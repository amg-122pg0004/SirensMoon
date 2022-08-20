#include "Boss.h"
#include "Game.h"
#include "ModeGame.h"
#include "BossCanon.h"
#include "BossMissile.h"
#include "DisplayArea.h"

Boss::Boss(Game& game, ModeGame& mode) 
	:Actor(game,mode),_scale{1.0},_angle{0},_animNo{0}
	,_backlayer{true},_time{60},_visible{true},_speed{2.5}
	,_headbuttSize{150,420},_headSize{90,90}
{
	_pos = { 500,500 };
	_size = { 420,840 };

	std::vector<int> handle;
	handle.resize(1);
	ImageServer::LoadDivGraph("resource/Boss/wait.png",1,1,1,420,840,handle.data());
	_cg[State::Wait] = handle;
	ImageServer::LoadDivGraph("resource/Boss/gunattack1.png", 1, 1, 1, 420, 840, handle.data());
	_cg[State::GunAttack1] = handle;
	_cg[State::GunAttack2] = handle;
	ImageServer::LoadDivGraph("resource/Boss/missileattack.png", 1, 1, 1, 420, 840, handle.data());
	_cg[State::ShootMissile] = handle;
	ImageServer::LoadDivGraph("resource/Boss/headbutt.png", 1, 1, 1, 420, 840, handle.data());
	_cg[State::HeadButt] = handle;

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

	--_time;

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
		_angle = 0;
	}
}

void Boss::BackRender(Vector2 window_pos, Vector2 camera_pos){
	if (_visible) {
		if (_backlayer) {
			auto cg = _cg[_state];
			DrawRotaGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
				static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
				_scale, _angle, cg[_animNo], 0, 0);
		}
	}
}

void Boss::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	if (_visible) {
		if (!_backlayer) {
			auto cg = _cg[_state];
			DrawRotaGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
				static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
				_scale, _angle, cg[_animNo], 0, 0);
		}
	}
}

void Boss::Wait() {
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
		_time = 1200;
		HeadButt();
		break;
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
	if (1150 == _time) {
		_scale = 0.25;
		_pos.y += 100;
		_backlayer = false;
	}
	if (1090 == _time) {
		//_visible = false;
	}

	if (_time == 1) {
		_scale = 1;
		_pos={500,500};
		_backlayer = true;
		_visible = true;
	}
	if (_time < 1090 && _time>790) {
		AABB col=_player1->GetCollision();
		auto dir = (col.min + col.max) / 2 - _pos;


		if (dir.Length() < 150&& dir.Length() > 50) {
			_angle = Math::ToRadians(90);
		}
		else {
			dir.Normalize();
			_pos = _pos + dir * _speed;
		}

		UpdateCollision();
	}

}

void Boss::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	/*
	DrawFormatString(static_cast<int>(_pos.x-camera_pos.x+window_pos.y),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		GetColor(255,0,0),"%d",_time);
		*/

	AABB col = _player1->GetCollision();
	auto dir = (col.min + col.max) / 2 - _pos;
	auto test = dir.Length();
	DrawFormatString(static_cast<int>(_pos.x - camera_pos.x + window_pos.y),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		GetColor(255, 0, 0), "%d", dir.Length());

}

void Boss::UpdateCollision(){
	_collision.min = _pos;
	_collision.max = _pos + _size;
}
