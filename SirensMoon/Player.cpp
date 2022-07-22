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
#include "ProjectionLight.h"
#include "LightBase.h"

Player::Player(Game& game,ModeBase& mode,int playernum)
	:Actor{ game,mode }, _speed{ 0,0 },_speedMax{5.0}, _playerNum{playernum}
	, _lastDir{1,0},_hp{3},_bullet{5},_movable{1},_charge{0},_cooldown{0}
{
	_inputManager = _game.GetInputManager();
	 _cg_up = ImageServer::LoadGraph("resource/player/up.png");
	 _cg_side = ImageServer::LoadGraph("resource/player/side.png");
	 _cg_down = ImageServer::LoadGraph("resource/player/down.png");
	 _cg_recon = ImageServer::LoadGraph("resource/player/recon.png");
	 _cg_dead = ImageServer::LoadGraph("resource/player/dead.png");

	 Vector2 pos = dynamic_cast<ModeGame&>(_mode).GetMapChips()->GetPlayerStartPosition(_playerNum);
	 _pos = { pos.x,pos.y };
	 _stage = 1;

	 auto light = std::make_unique<LightBase>(_game, _mode, *this);
	 _mode.GetActorServer().Add(std::move(light));
}

void Player::Update() {

	/*アナログ入力取得*/
	_dir = _inputManager->CheckAnalogInput(_playerNum);

	if (_dir.Length() != 0) {
		_dir.Normalize();
		_lastDir = _dir;
	}


	if (_playerNum == 0) {
		GunShoot();
	}
	if (_playerNum == 1) {
		OpenMap();
	}

	if (_movable) {
		Move();
	}

	UpdateCollision();
}


void Player::Move() {
	


	/*障害物衝突処理*/
	/*X方向*/
	_pos.x += _dir.x * _speedMax;
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips() ->IsHit(_stage - 1, *this)) {
		_pos.x += -1*_dir.x  * _speedMax;
	}
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHitBarrier(_stage - 1, *this, _playerNum)) {
		_pos.x += -1 * _dir.x * _speedMax;
	}
	UpdateCollision();
	if (IsHitActor()) {
		_pos.x += -1 * _dir.x * _speedMax;
	}


	_pos.y += _dir.y * _speedMax;
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips() ->IsHit(_stage - 1, *this)) {
		_pos.y += -1 * _dir.y  * _speedMax;
	}
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHitBarrier(_stage - 1, *this, _playerNum)) {
		_pos.x += -1 * _dir.y * _speedMax;
	}
	UpdateCollision();
	if (IsHitActor()) {
		_pos.y += -1 * _dir.y * _speedMax;
	}
	
	
	
	/*ステージ外に出ないようにする処理*/
	if (_pos.x < 0) {
		_pos.x = 0;
	}
	else if (static_cast<int>(_pos.x)+_size.x > screen_W / 2 * 3) {
		_pos.x = screen_W / 2 * 3-_size.x;
	}

	if (_pos.y < 0) {
		_pos.y = 0;
	}
	else if (static_cast<int>(_pos.y)+_size.y> screen_H * 3) {
		_pos.y = screen_H * 3-_size.y;
	}

	/*フレームアウトした際にカメラを動かす処理*/
	auto&& rendercamera = dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[_playerNum]->GetCamera();
	Vector2 renderposition = _pos - rendercamera->GetPosition();

	if (renderposition.x < 0 && _dir.x < 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::LEFT);
	}
	else if (renderposition.x > static_cast<double>(screen_W) / 2 && _dir.x > 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::RIGHT);
	}
	if (renderposition.y < 0 && _dir.y < 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::UP);
	}
	else if (renderposition.y > screen_H&&_dir.y>0) {
		rendercamera->ChangePosition(Camera::ChangeDir::DOWN);
	}
	
}

bool Player::IsHitActor() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() != Type::Player&& actor->GetType()!=Type::Item) {
			if (Intersect(_collision, actor->GetCollision())) {
				return true;
			}
		}

	}
	return false;
}

void Player::GunShoot() {
	--_cooldown;
	if (_cooldown < 0) {
		_cooldown = 0;
	}

	if (_inputManager->CheckInput("ACTION",'r', _playerNum)&&_charge>=120) {
		_lastDir.Normalize();
		if (_bullet > 0) {
			auto bullet = std::make_unique<Bullet>(_game, _mode, _pos, _lastDir);
			_mode.GetActorServer().Add(std::move(bullet));
			//--_bullet;
			_cooldown = 180;
		}
		
	}

	if (_inputManager->CheckInput("ACTION", 'h', _playerNum)&&_cooldown==0) {
		_movable = 0;
		if (_charge == 0) {
			auto gunlight = std::make_unique<ProjectionLight>(_game, _mode, *this);
			_mode.GetActorServer().Add(std::move(gunlight));
		}

		++_charge;
	}
	else {
		_movable = 1;
		_charge = 0;
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
	if (_hp < 1) {
		_cg = _cg_dead;
	}
		DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg, 0);
	}
}

void Player::UpdateCollision() {
	_collision.min = _pos;
	_collision.max = _pos + _size;
}

void Player::ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_recon, 0);
}

void Player::TakeDamage() {
	--_hp;
}

void Player::Heal() {
	++_hp;
}
void Player::TakeAmmo() {
	++_bullet;
}

void Player::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	//デバッグ用座標表示

	std::stringstream ss;
	ss << "HP" << _hp << "\n";
	if (_playerNum == 0) {
		ss << "弾薬" << _bullet << "\n";
	}

	//ss << "_collision.max.x" << _collision.max.x << "\n";
	//ss << "_collision.max.y" << _collision.max.y << "\n";
	ss << "チャージ" << _charge << "\n";
	ss << "方向" << _lastDir.x <<"  "<<_lastDir.y << "\n";
	ss << "プレイヤー" << _playerNum << "\n";
	DrawString(50 + _playerNum * 960, 100, ss.str().c_str(), GetColor(255, 0, 255));
}

