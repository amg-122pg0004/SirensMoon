#include "Boss.h"
#include "Game.h"
#include "ModeGame.h"
#include "BossCanon.h"
#include "BossMissile.h"
#include "DisplayArea.h"
#include "BossGimmickController.h"

Boss::Boss(Game& game, ModeGame& mode, BossGimmickController& controller)
	:Actor(game,mode),_scale{1.0},_animNo{0}
	,_backlayer{true},_time{60},_visible{true},_speed{2.5}
	,_headbuttSize{150,420},_headSize{90,90},_hp{6},_controller{controller}
{
	Vector2 pos = { _controller.GetRoomPosition().x-1.0,_controller.GetRoomPosition().y-1.0 };
	_startPos = { splitscreen_W * pos.x + 500 , screen_H * pos.y + 450 };
	_pos = _startPos;
	_size = { 100,200 };
	_size2 = { 400,500 };

	std::vector<int> handle;
	handle.resize(65);
	ImageServer::LoadDivGraph("resource/Boss/wait.png",65,10,7,1024,1024,handle.data());
	_cg[State::Wait] = handle;
	handle.resize(90);
	ImageServer::LoadDivGraph("resource/Boss/gunfire.png", 90, 10, 9, 1024, 1024, handle.data());
	_cg[State::GunAttack1] = handle;
	handle.resize(90);
	ImageServer::LoadDivGraph("resource/Boss/faint.png", 90, 10, 9, 1024, 1024, handle.data());
	_cg[State::GunAttack2] = handle;
	handle.resize(80);
	ImageServer::LoadDivGraph("resource/Boss/missileboss.png", 80, 10, 8, 1024, 1024, handle.data());
	_cg[State::ShootMissile] = handle;
	handle.resize(70);
	ImageServer::LoadDivGraph("resource/Boss/headbutt.png", 70, 10, 7, 1024, 1024, handle.data());
	_cg[State::HeadButt] = handle;
	handle.resize(70);
	ImageServer::LoadDivGraph("resource/Boss/jump.png", 70, 10, 7, 1024, 1024, handle.data());
	_cg[State::Jump] = handle;
	handle.resize(26);
	ImageServer::LoadDivGraph("resource/Boss/jump.png", 26, 10, 3, 1024, 1024, handle.data());
	_cg[State::Damage] = handle;
	handle.resize(180);
	ImageServer::LoadDivGraph("resource/Boss/thunder.png", 180, 10, 18, 1024, 1024, handle.data());
	_cg[State::Damage] = handle;

	_state = State::Wait;

	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			_player1 = actor.get();
		}
		if (actor->GetType() == Type::PlayerB) {
			_player2 = actor.get();
		}
	}
}

void Boss::Update(){
	UpdateCollision();
	CheckOverlapActor();
	--_time;
	if (_game.GetFrameCount() % 3 == 0) {
		++_animNo;
	}
	switch (_state)
	{
	case Boss::State::Wait:
		Wait();
		break;
	case Boss::State::GunAttack1:
		GunAttack1();
		break;
	case Boss::State::GunAttack2:
		GunAttack2();
		break;
	case Boss::State::ShootMissile:
		ShootMissile();
		break;
	case Boss::State::Jump:
		break;
	case Boss::State::HeadButt:
		HeadButt();
		break;
	case Boss::State::TakeDamage:
		break;
	}
	if (_time < 0&&_state!=State::Wait) {
		_time = 60;
		_state = State::Wait;
	}
}

void Boss::CheckOverlapActor() {
	if (_visible && !_backlayer) {
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Type::RedBullet) {
				if (Intersect(_collision,actor->GetCollision())) {
					TakeDamage();
				}
			}
		}
	}
}

void Boss::TakeDamage() {
	--_hp;
	_backlayer = true;
	if (_hp <= 3) {
		if (!_phase2) {
			_phase2 = true;
			_controller.Phase2();
		}
	}
	if (_hp <= 0) {
		_dead = true;
	}
	_time = 1;
	_scale = 1;
	_pos = _startPos;
	_backlayer = true;
	_visible = true;
}

void Boss::BackRender(Vector2 window_pos, Vector2 camera_pos){
	if (_visible) {
		if (_backlayer) {
			auto cg = _cg[_state];
			if (_animNo >= cg.size() - 1) {
				_animNo = 0;
			}
			DrawRotaGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
				static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
				_scale, 0.0, cg[_animNo], 1);
		}
	}
}

void Boss::StandardRender( Vector2 window_pos, Vector2 camera_pos) {
	if (_visible) {
		if (!_backlayer) {
			auto cg = _cg[_state];
			if (_animNo>=cg.size()-1) {
				_animNo = 0;
			}
			DrawRotaGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
				static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
				_scale, 0.0, cg[_animNo], 1);
		}
	}
}

void Boss::Wait() {

	_animNo=0;
	if (!_phase2) {
		switch (rand3(engine)) {
		case 1:
			if (rand2(engine) == 1) {
				_time = 150;
				GunAttack1();
				break;
			}
			else {
				_time = 150;
				GunAttack2();
				break;
			}
		case 2:
			_time = 300;
			ShootMissile();
			break;

		case 3:
			_time = 750;
			HeadButt();
			break;
		}
	} else
		{
		switch (rand2(engine)) {
		case 1:
			if (rand2(engine) == 1) {
				_time = 150;
				GunAttack1();
				break;
			}
			else {
				_time = 150;
				GunAttack2();
				break;
			}
		case 2:
			_time = 300;
			ShootMissile();
			break;
		}
	}
}

void Boss::GunAttack1() {
	_state = State::GunAttack1;
	_mode.GetActorServer().Add(std::make_unique<DisplayArea>(_game, _mode, *this,true));
	if (_time == 30) {
		Vector2 fix{ -600,0 };
		_mode.GetActorServer().Add(std::make_unique<BossCanon>(_game, _mode, _pos + fix));
	}
}

void Boss::GunAttack2() {
	_state = State::GunAttack2;
	_mode.GetActorServer().Add(std::make_unique<DisplayArea>(_game, _mode, *this,false));
	if (_time == 30) {
		Vector2 fix{ 0,0 };
		_mode.GetActorServer().Add(std::make_unique<BossCanon>(_game, _mode, _pos + fix));
	}
}

void Boss::ShootMissile() {
	_state = State::ShootMissile;
	if (_time == 300|| _time == 280|| _time == 260) {
		Vector2 rand = { static_cast<double>(rand100(engine)) / 100 * splitscreen_W,0 };
		_mode.GetActorServer().Add(std::make_unique<BossMissile>(_game, _mode, rand));
	}
}

void Boss::HeadButt(){

	_state = State::HeadButt;

	if (700 == _time) {
		_scale = 0.25;
		_pos.y += 100;
		_backlayer = false;
	}
	if (590 == _time) {
		_visible = false;
	}

	if (_time == 1) {
		_scale = 1;
		_pos=_startPos;
		_backlayer = true;
		_visible = true;
	}

	if (_time < 590 && _time>410&&_visible==false) {
		AABB col=_player1->GetCollision();
		auto dir = (col.min + col.max) / 2 - _pos;

		if (dir.Length() < 150&& dir.Length() > 100) {
			_visible = true;
		}
		else {
			dir.Normalize();
			_pos = _pos + dir * _speed;
		}
		UpdateCollision();
	}
}

void Boss::Debug(Vector2 window_pos, Vector2 camera_pos){

	AABB col = _player1->GetCollision();
	auto dir = (col.min + col.max) / 2 - _pos;
	auto test = dir.Length();

	DrawFormatString(static_cast<int>(_pos.x - camera_pos.x + window_pos.y),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		GetColor(255, 0, 0), "%lf", _collision.min.x);
	_hitbox.Draw2(window_pos, camera_pos);

}

void Boss::UpdateCollision(){
	if (_backlayer) {
		_collision.min = { _pos.x - _size2.x / 2,_pos.y - _size2.y * 0.8 };
		_collision.max = { _pos.x + _size2.x / 2,_pos.y + _size2.y * 0.2 };
		_hitbox.min = { _pos.x - _size2.x / 2,_pos.y - _size2.y * 0.8 };
		_hitbox.max = { _pos.x + _size2.x / 2,_pos.y + _size2.y * 0.2 };
	}
	else {
		_collision.min = _pos - _size / 2;
		_collision.max = _pos + _size / 2;
		_hitbox.min = _pos - _size / 2;
		_hitbox.max = _pos + _size / 2;
	}
}

void Boss::Jump(){

}

void Boss::Thunder(){

}
