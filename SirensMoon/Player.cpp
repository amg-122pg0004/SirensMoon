/*****************************************************************//**
 * \file   Player.h
 * \brief プレイヤーキャラ
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "Player.h"
#include "ImageServer.h"
#include "MapChip.h"
#include <string>
#include <sstream>

#include "Bullet.h"
#include "Game.h"
#include "ModeGame.h"


Player::Player(Game& game,ModeBase& mode,int playernum)
	:Actor{ game,mode }, _speed{ 0,0 },_speedMax{5.0}, _playerNum{playernum}
	,_stress{ 0 }, _stressSpeed{ 0.05f }, _lastDir{1,0}
{

	_inputManager = _game.GetInputManager();
	 _cg_up = ImageServer::LoadGraph("resource/player/up.png");
	 _cg_side = ImageServer::LoadGraph("resource/player/side.png");
	 _cg_down = ImageServer::LoadGraph("resource/player/down.png");
	 _cg_recon = ImageServer::LoadGraph("resource/player/recon.png");

	 _pos = { 200,200 };
	 _stage = 1;

	 _validLight = true;
	 //_light = std::make_unique<Light1>(_game, *this);
}

void Player::Update() {

	CheckStress();
	Move();
	if (_playerNum == 0) {
		GunShoot();
	}
	if (_playerNum == 1) {
		OpenMap();
	}
}


void Player::Move() {
	
	_dir=_inputManager->CheckAnalogInput(_playerNum);
	if (_dir.Length() != 0) {
		_lastDir = _dir;
	}

	/*障害物衝突処理*/
	
	_pos.x += _dir.x/1000*_speedMax;
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips() ->IsHit(_stage - 1, *this)) {
		_pos.x += -1*_dir.x / 1000 * _speedMax;
	}

	_pos.y += _dir.y / 1000 * _speedMax;
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips() ->IsHit(_stage - 1, *this)) {
		_pos.y += -1 * _dir.y / 1000 * _speedMax;
	}
	
	/*ステージ外に出ないようにする処理*/
	if (_pos.x < 0) {
		_pos.x = 0;
	}
	else if (_pos.x > screen_W / 2 * 3) {
		_pos.x = screen_W / 2 * 3;
	}

	if (_pos.y < 0) {
		_pos.y = 0;
	}
	else if (_pos.y > screen_H * 3) {
		_pos.y = screen_H * 3;
	}

	/*フレームアウトした際にカメラを動かす処理*/
	auto&& rendercamera = dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[_playerNum]->GetCamera();
	Vector2 renderposition = _pos - rendercamera->GetPosition();

	if (renderposition.x < 0 && _dir.x < 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::LEFT);
	}
	else if (renderposition.x > screen_W / 2 && _dir.x > 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::RIGHT);
	}
	if (renderposition.y < 0 && _dir.y < 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::UP);
	}
	else if (renderposition.y > screen_H&&_dir.y>0) {
		rendercamera->ChangePosition(Camera::ChangeDir::DOWN);
	}
	
}

void Player::GunShoot() {
	if (_inputManager->CheckInput("ACTION",'t', _playerNum)) {
		_lastDir.Normalize();
		auto bullet = std::make_unique<Bullet>(_game,_mode, _pos,_lastDir);
		_mode.GetActorServer().Add(std::move(bullet));
	}
}

void Player::OpenMap() {
	if (_inputManager->CheckInput("ACTION", 't', _playerNum)) {
		
	}
}

void Player::StandardRender(int stageNum,Vector2 window_pos,Vector2 camera_pos){
	int _cg = -1;
	if (_stage == stageNum) {
		if (abs(_lastDir.x) > abs(_lastDir.y)) {
			_cg = _cg_side;
		}
		else {
			if (_lastDir.y < 0) {
				_cg = _cg_up;
			}
			else {
				_cg = _cg_down;
			}
		}
		DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg, 0);
	}
}

void Player::ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_recon, 0);
}

void Player::CheckStress(){
	for (auto&& actor:_mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Actor::Type::Player) {
			if (dynamic_cast<Player*>(actor.get())->GetPlayerNum() != _playerNum) {
				if ((actor->GetPosition() - _pos).Length() < 200) {
					_stress=_stress-_stressSpeed*4;
				}
			}
		}
	}

	_stress = _stress + _stressSpeed;

	_stress = Math::Clamp(_stress,0.0f,100.0f);
}

void Player::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	//デバッグ用座標表示

	std::stringstream ss;

	//ss << (_pos.x + _size.x / 2) / _game.GetMapChips()->GetChipSize_W()<<"\n";
	//ss << (_pos.y + _size.y / 2) / _game.GetMapChips()->GetChipSize_H() << "\n";
	//ss << "_pos.x"<<_pos.x<<"\n";
	//ss << "_pos.y" << _pos.y << "\n";

	//ss << "ストレス" << round(_stress) << "%" << "\n";
	ss << "_dir.x" << _speed.x << "\n";
	ss << "_dir.y" << _speed.y << "\n";
	ss << "_speed.x" << _speed.x << "\n";
	ss << "_speed.y" << _speed.y << "\n";
	DrawString(500 + _playerNum * 800, 100, ss.str().c_str(), GetColor(0, 255, 255));
}
