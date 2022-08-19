#include "Boss.h"
#include "ModeGame.h"
#include "BossCanon.h"
#include "DisplayArea.h"

Boss::Boss(Game& game, ModeGame& mode) 
	:Actor(game,mode),_scale{1.0},_angle{0},_animNo{0},_backlayer{true},_time{60}
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
	if(_state==State::Wait && _time < 0){
		_time = 120;
		switch (rand3(engine)) {
		case 1:
			if (rand2(engine) == 1) {

				GunAttack1();
				break;
			}
			else {
				GunAttack2();
				break;
			}
		case 2:
			GunAttack1();
			//ShootMissile();
			break;

		case 3:
			GunAttack1();
			//HeadButt();
			break;
		}
	}
	if (_state == State::GunAttack1) {
		GunAttack1();
	}
	if (_state == State::GunAttack2) {
		GunAttack2();
	}

	if (_time < 0) {
		_time = 60;
		_state = State::Wait;
	}
}

void Boss::BackRender(Vector2 window_pos, Vector2 camera_pos){
	if (_backlayer) {
		auto cg = _cg[_state];
		DrawRotaGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
			static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
			_scale, _angle, cg[_animNo], 0, 0);
	}
}

void Boss::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	if (!_backlayer) {
		auto cg = _cg[_state];
		DrawRotaGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
			static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
			_scale, _angle, cg[_animNo], 0, 0);
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
}

void Boss::HeadButt(){
	_state = State::HeadButt;
	
}

void Boss::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	DrawFormatString(static_cast<int>(_pos.x-camera_pos.x+window_pos.y),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		GetColor(255,0,0),"%d",_time);
}
