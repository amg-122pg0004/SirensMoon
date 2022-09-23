#include "Boss.h"
#include "Game.h"
#include "ModeGame.h"
#include "BossCanon.h"
#include "BossMissile.h"
#include "DisplayArea.h"
#include "BossGimmickController.h"
#include "ObjectiveUI.h"
#include "Explode.h"
#include "FX_BossDead.h"
#include "BossWeakPoint.h"
#include "FX_MissileShoot.h"

Boss::Boss(Game& game, ModeGame& mode, BossGimmickController& controller)
	:Actor(game, mode), _scale{ 1.0 }, _mapscale{ 1.0 }, _animNo{ 0 }
	, _backlayer{ true }, _time{ 60 }, _visible{ true }, _speed{ 2.5 }, _alpha{ 255 }
	, _headbuttSize{ 150,420 }, _headSize{ 90,90 }, _hp{ 1 }, _controller{ controller }
	, _phase2{ false }, _player1{ nullptr }, _player2{ nullptr }, _invincible{ true }
	,_stop{false}
{
	Vector2 pos = { _controller.GetRoomPosition().x - 1.0,_controller.GetRoomPosition().y - 1.0 };
	_startPos = { splitscreen_W * pos.x + 500 , screen_H * pos.y + 450 };
	_shootPos = { _startPos.x,_startPos.y - 230 };
	_pos = _startPos;
	_size = { 100,200 };
	_size2 = { 400,500 };
	std::vector<int> handle,handle2;
	handle.resize(65);
	ImageServer::LoadDivGraph("resource/Boss/wait2.png", 65, 10, 7, 640, 740, handle.data());
	_cg[State::Wait] = handle;
	handle.resize(40);
	ImageServer::LoadDivGraph("resource/Boss/gunfireA.png", 40, 10, 4, 1024, 1024, handle.data());
	handle2.resize(50);
	ImageServer::LoadDivGraph("resource/Boss/gunfireB1.png", 50, 10, 5, 1024, 1024, handle2.data());
	handle.insert(handle.end(), handle2.begin(), handle2.end());
	_cg[State::GunAttack1] = handle;
	handle.resize(40);
	ImageServer::LoadDivGraph("resource/Boss/gunfireA.png", 40, 10, 4, 1024, 1024, handle.data());
	handle2.resize(50);
	ImageServer::LoadDivGraph("resource/Boss/gunfireB2.png", 50, 10, 5, 1024, 1024, handle2.data());
	handle.insert(handle.end(), handle2.begin(), handle2.end());
	_cg[State::GunAttack2] = handle;
	handle.resize(80);
	ImageServer::LoadDivGraph("resource/Boss/missileboss2.png", 80, 10, 8, 840, 740, handle.data());
	_cg[State::ShootMissile] = handle;
	handle.resize(70);
	ImageServer::LoadDivGraph("resource/Boss/headbutt.png", 70, 10, 7, 256, 256, handle.data());
	_cg[State::HeadButt] = handle;
	handle.resize(70);
	ImageServer::LoadDivGraph("resource/Boss/jump.png", 70, 10, 7, 1024, 1024, handle.data());
	_cg[State::Jump] = handle;
	_cg[State::Return] = handle;
	handle.resize(26);
	ImageServer::LoadDivGraph("resource/Boss/damage.png", 26, 10, 3, 256, 256, handle.data());
	_cg[State::Damage] = handle;
	handle.resize(180);
	ImageServer::LoadDivGraph("resource/Boss/thunder2.png", 180, 10, 18, 1024, 740, handle.data());
	_cg[State::Thunder] = handle;
	_time = 3 * 60;
	_state = State::Wait;

	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			_player1 = actor.get();
		}
		if (actor->GetType() == Type::PlayerB) {
			_player2 = actor.get();
		}
	}
	int i{ 0 };
	for (auto&& window : _mode.GetSplitWindow()) {
		Vector2 pos{ 0,0 }, size{ 90,90 };
		window->GetUIServer2().Add(std::make_unique<BossWeakPoint>(_game, _mode, *window, pos, size, *this, i));
		++i;
	}
}

void Boss::Update() {
	if (_stop) {
		return;
	}
	UpdateCollision();
	CheckOverlapActor();
	if (_game.GetFrameCount() % 3 == 0) {
		++_animNo;
	}
	--_time;
	if (_time < 0) {
		if (_state != Boss::State::Wait) {
			_time = 90;
			_state = State::Wait;
		}
		else {
			ChoiceAttack();
		}
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
		Jump();
		break;
	case Boss::State::HeadButt:
		HeadButt();
		break;
	case Boss::State::Damage:
		DamageSequence();
		break;
	case Boss::State::Thunder:
		Thunder();
		break;
	case Boss::State::Return:
		Return();
		break;
	}

}

void Boss::CheckOverlapActor() {
	if (_state == State::HeadButt && _animNo > 65 && _visible) {
		_invincible = false;
	}
	else {
		_invincible = true;
	}
	if (_invincible) {
		return;
	}
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::RedBullet) {
			if (Intersect(_hitbox, actor->GetCollision())) {
				TakeDamage();
				actor->Dead();
			}
		}
	}
}

void Boss::TakeDamage() {
	if (_state != State::Damage) {
		--_hp;
		_time = 26 * 3;
		_state = State::Damage;
	}
}
void Boss::DamageSequence() {
	if (_time == 0) {
		_time = 4 * 60;
		_animNo = 0;
		_scale = 0.25;
		_state = State::Return;
	}
}

void Boss::BackRender(Vector2 window_pos, Vector2 camera_pos) {
	if (_visible) {
		if (_backlayer) {
			Vector2 fix{ 0,0 };
			if (_state == State::Wait||_state==State::Thunder||_state==State::ShootMissile) {
				fix = { 0,-142 };
			}

			auto cg = _cg[_state];
			if (_animNo >= cg.size()) {
				_animNo = 0;
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
			DrawRotaGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x+ fix.x),
				static_cast<int>(_pos.y - camera_pos.y + window_pos.y+ fix.y),
				_scale, 0.0, cg[_animNo], 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}
}

void Boss::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	if (_visible) {
		if (!_backlayer) {
			auto cg = _cg[_state];
			if (_animNo >= cg.size()) {
				_animNo = 0;
			}

			DrawRotaGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
				static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
				_scale, 0.0, cg[_animNo], 1);

		}
	}
}

void Boss::ChoiceAttack() {
	_animNo = 0;
	if (!_phase2) {
		switch (rand3(engine)) {
		//switch (2) {
		case 1:
			if (rand2(engine) == 1) {
				_time = 270;
				GunAttack1();
				break;
			}
			else {
				_time = 270;
				GunAttack2();
				break;
			}
		case 2:
			_time = 240;
			ShootMissile();
			break;

		case 3:
			_time = 2.5 * 60;
			Jump();
			break;
		}
	}
	else
	{
		switch (rand2(engine)) {
		case 1:
			if (rand2(engine) == 1) {
				_time = 270;
				GunAttack1();
				break;
			}
			else {
				_time = 270;
				GunAttack2();
				break;
			}
		case 2:
			_time = 240;
			ShootMissile();
			break;
		}
	}
}

void Boss::Wait() {
	_pos.y += 5;
	if (_pos.y > _startPos.y) {
		_pos.y = _startPos.y;
	}

}

void Boss::GunAttack1() {
	_state = State::GunAttack1;
	if (_time == 270) {
		_mode.GetActorServer().Add(std::make_unique<DisplayArea>(_game, _mode, *this, true));
	}
	if (_time < 270 && _time>220) {
		_pos.y -= 5;
		if (_pos.y < _startPos.y - 230) {
			_pos.y = _startPos.y - 230;
		}
	}
	if (_time == 175) {
		Vector2 fix{ -600,0 };

		_mode.GetActorServer().Add(std::make_unique<BossCanon>(_game, _mode, _pos + fix));
	}
	if (!_phase2) {
		dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
			->ChangeMessage("マップから射線を読みとり、回避せよ", 1);
		dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()
			->ChangeMessage("マップから射線を読みとり、回避せよ", 1);
	}
}

void Boss::GunAttack2() {
	_state = State::GunAttack2;
	if (_time == 270) {
		_mode.GetActorServer().Add(std::make_unique<DisplayArea>(_game, _mode, *this, false));
	}
	if (_time < 270 && _time>220) {
		_pos.y -= 5;
		if (_pos.y < _startPos.y - 230) {
			_pos.y = _startPos.y - 230;
		}
	}
	if (_time == 110) {
		Vector2 fix{ 0,0 };
		_mode.GetActorServer().Add(std::make_unique<BossCanon>(_game, _mode, _pos + fix));

	}
	if (!_phase2) {
		dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
			->ChangeMessage("マップから射線を読みとり、回避せよ", 2);
		dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()
			->ChangeMessage("マップから射線を読みとり、回避せよ", 1);
	}
}

void Boss::ShootMissile() {
	_state = State::ShootMissile;
	if (_time==100)
	{
		Vector2 fix{200,-400};
		_mode.GetActorServer().Add(std::make_unique<FX_MissileShoot>(_game, _mode, _pos + fix,_game.GetFrameCount()));
		PlaySoundMem(SoundServer::Find("MissileLaunch"), DX_PLAYTYPE_BACK);
	}

	if (_time == 40 || _time == 20 || _time == 0) {
		Vector2 rand = { static_cast<double>(rand100(engine)) / 100 * splitscreen_W,0 };
		_mode.GetActorServer().Add(std::make_unique<BossMissile>(_game, _mode, rand));
	}
	if (!_phase2) {
		dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
			->ChangeMessage("ミサイルを撃ち落とせ", 1);
		dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()
			->ChangeMessage("ミサイルを回避せよ", 2);
	}
}

void Boss::HeadButt() {

	_state = State::HeadButt;

	if (700 == _time) {
		_scale = 1;
		_pos = _startPos;
		switch (rand3(engine)) {
		case 1:
			_pos.y += 100;
			break;
		case 2:
			_pos.x -= 400;
			_pos.y += 200;
			break;
		case 3:
			_pos.x += 400;
			_pos.y += 200;
			break;
		}
		_backlayer = false;
		_visible = false;
	}

	if (_time == 1) {
		_time = 4 * 60;
		_animNo = 0;
		_scale = 0.25;
		_state = State::Return;
	}

	if (_time < 590 && _time>410 && _visible == false) {
		if (CheckSoundMem(SoundServer::Find("PreHeadbutt"))==0) {
			PlaySoundMem(SoundServer::Find("PreHeadbutt"), DX_PLAYTYPE_BACK);
		}
		AABB col = _player1->GetCollision();
		auto dir = (col.min + col.max) / 2 - _pos;

		if (dir.Length() < 150 && dir.Length() > 100) {
			_visible = true;
			_animNo = 0;
		}
		else {
			dir.Normalize();
			_pos = _pos + dir * _speed;
		}
		UpdateCollision();
	}

	if (_time <= 410 && _visible == false) {
		_visible = true;
		_animNo = 0;
		StopSoundMem(SoundServer::Find("PreHeadbutt"));
	}

	if (_visible == true) {
		if (_animNo < 20) {
			_pos.y -= 3;
		}
		if (_animNo >= 20 && _animNo < 30) {
			_pos.y += 6;
		}
		if (_animNo == 30) {
			Vector2 pos = { _pos.x,_pos.y + _size.y / 2 };
			_mode.GetActorServer().Add(std::make_unique<Explode3>(_game, _mode, pos));
			if (CheckSoundMem(SoundServer::Find("Headbutt")) == 0) {
				PlaySoundMem(SoundServer::Find("Headbutt"), DX_PLAYTYPE_BACK);
			}
		}
	}

	if (_animNo >= 70) {
		_animNo = 69;
	}

}

void Boss::Debug(Vector2 window_pos, Vector2 camera_pos) {

	AABB col = _player1->GetCollision();
	auto dir = (col.min + col.max) / 2 - _pos;
	auto test = dir.Length();

	DrawFormatString(static_cast<int>(_pos.x - camera_pos.x + window_pos.y),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		GetColor(255, 0, 0), "%d", _time);
	_collision.Draw2(window_pos, camera_pos);
	_hitbox.Draw2(window_pos, camera_pos);
}

void Boss::UpdateCollision() {
	if (_backlayer) {
		_collision.min = { _pos.x - _size2.x / 2,_pos.y - _size2.y * 0.8 };
		_collision.max = { _pos.x + _size2.x / 2,_pos.y + _size2.y * 0.2 };
		_hitbox.min = { _pos.x - _headSize.x / 2,_pos.y - _headSize.y / 2 - 100 };
		_hitbox.max = _hitbox.min + _headSize;
	}
	else {
		_collision.min = _pos - _size / 2;
		_collision.max = _pos + _size / 2;
		_hitbox.min = { _pos.x - _headSize.x / 2,_pos.y - _headSize.y / 2 - 100 };
		_hitbox.max = _hitbox.min + _headSize;
	}
}

/*全体150F*/
void Boss::Jump() {
	_state = State::Jump;
	if (_time < 150 && _time > 90) {
		_scale -= 0.01;
		_mapscale -= 0.01;
		if (_scale < 0.25) {
			_scale = 0.25;
			_mapscale = 0.25;
		}
	}
	if (_time < 120 && _time > 0) {
		_alpha -= 2;
	}
	if (_time < 45) {
		_pos.y -= 40;
	}
	if (_time == 0) {
		_time = 800;
		_alpha = 255;
		_visible = false;
		_state = State::HeadButt;
	}
	dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
		->ChangeMessage("消えた敵の攻撃を避け、\n隙をついて攻撃せよ", 2);
	dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()
		->ChangeMessage("消えた敵の位置をマップから探れ", 1);
}

/*全体150F*/
void Boss::Return() {
	_state = State::Return;
	if (_time < 165 && _time>80) {
		_pos.y -= 40;
	}
	if (_time == 80) {
		_scale = 1;
		_mapscale = 1;
		_backlayer = true;
		_visible = true;
		_pos.x = _startPos.x;
	}
	if (_time < 80) {
		Vector2 dir = _startPos - _pos;
		dir.Normalize();
		if (_pos.y < _startPos.y) {
			_pos.y = _startPos.y;
		}
	}
	if (_time == 1) {
		_pos = _startPos;
		if (_hp <= 0) {
			if (!_phase2) {
				_state = State::Thunder;
				_time = 500;
				_scale = 1;
				_mapscale = 1;
				_pos = _startPos;
				_backlayer = true;
				_visible = true;
				return;
			}
		}
	}
}

void Boss::Thunder() {
	if (_time == 180) {
		_controller.PrePhase2();
	}
	if (_time == 130) {
		_phase2 = true;
		_controller.Phase2();
	}
}

void Boss::Dead() {
	_mode.GetActorServer().Add(std::make_unique<FX_BossDead>(_game, _mode, _pos, _game.GetFrameCount()));
	_stop = true;
}
