/*****************************************************************//**
 * \file   Player.h
 * \brief プレイヤーキャラ
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "Player.h"
#include "MapChip.h"
#include <string>
#include <sstream>
#include <mutex>
#include "Bullet.h"
#include "Game.h"
#include "ModeGame.h"
#include "ProjectionLight.h"
#include "LightBase.h"
#include "teleporter.h"

Player::Player(Game& game,ModeGame& mode,int playernum)
	:Actor{ game,mode }, _speed{ 0,0 },_speedMax{5.0}, _playerNum{playernum}
	, _dir{0,0}, _lastDir{ 1,0 }, _hp{ 3 },_hpMAX{3}, _bullet{5}, _movable{1}, _charge{0}, _cooldown{0}
	,_init{false},_state{PlayerState::Wait},_direction{PlayerDirection::Right},_animNo{0}, _invincibleTime{0}
{
	_inputManager = _game.GetInputManager();

	 Vector2 pos = _mode.GetMapChips()->GetPlayerStartPosition(_playerNum);
	 _pos = { pos.x,pos.y };
	 _stage = 1;
	 _size = { 30,60 };
	 auto light = std::make_unique<LightBase>(_game, _mode, *this);
	 _mode.GetActorServer().Add(std::move(light));
}

void Player::Init() {
	auto&& rendercamera = _mode.GetSplitWindow()[_playerNum]->GetCamera();
	rendercamera->SetPosition(_pos);
}

void Player::Update() {

	if (_init == false) {
		Init();
		_init = true;
	}

	/*アナログ入力取得*/
	_dir = _inputManager->CheckAnalogInput(_playerNum);
	_dir = _dir/1000;

	if (_dir.Length() != 0) {
		_lastDir = _dir;
		//_lastDir.Normalize();
	}

	if (_dir.Length() > 1) {
		_dir.Normalize();
	}
	PlayerOverlap();
	/*移動*/
	Move();
	/*テレポートに触れていたら起動*/
	Checkteleport();
	/*固有のアクション*/
	Action();
	/*コリジョンの更新*/
	UpdateCollision();
	/*敵かダメージギミックに触れていたらダメージ*/
	CheckDamage();
	/*自分の位置を確認*/
	CheckRoomPosition();
}

void Player::PlayerOverlap() {
	/*
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Player) {
			if (dynamic_cast<Player&>(*actor).GetPlayerNum() != _playerNum) {
				if(Intersect(_collision, actor->GetCollision())) {
					Vector2 col1_centerpos = (_collision.min + _collision.max) / 2;
					Vector2 col2_centerpos = (actor->GetCollision().max + actor->GetCollision().min) / 2;
					Vector2 dir = col2_centerpos - col1_centerpos;
					auto min_dir=min(dir.x, dir.y);
				}
			}
		}
	}
	*/
}

void Player::Move() {
	

	if (_movable){
		_speed = _speed + _dir * 0.2;
	}
	auto dir = _dir;
	if (dir.Length() == 0||!_movable) {
		_speed *= 0.9;
	}

	if (_speed.x > _speedMax) {
		_speed.x = _speedMax;
	}
	if (_speed.x < -_speedMax) {
		_speed.x = -_speedMax;
	}
	if (_speed.y > _speedMax) {
		_speed.y = _speedMax;
	}
	if (_speed.y < -_speedMax) {
		_speed.y = -_speedMax;
	}

	auto tmpspeed = _speed;
	if (tmpspeed.Length() > _speedMax) {
		_speed.Normalize();
		_speed *= _speedMax;
	}
	

	/*障害物衝突処理*/
	/*X方向*/
	_pos.x += _speed.x;
	if (_mode.GetMapChips() ->IsHit(*this)) {
		_pos.x += -1*_speed.x;
	}
	if (_mode.GetMapChips()->IsHitBarrier(_stage - 1, *this, _playerNum)) {
		_pos.x += -1 * _speed.x;
	}
	UpdateCollision();
	if (IsHitActor()) {
		_pos.x += -1 * _speed.x;
	}

	_pos.y += _speed.y;
	if (_mode.GetMapChips() ->IsHit(*this)) {
		_pos.y += -1 * _speed.y;
	}
	if (_mode.GetMapChips()->IsHitBarrier(_stage - 1, *this, _playerNum)) {
		_pos.y += -1 * _speed.y;
	}
	UpdateCollision();
	if (IsHitActor()) {
		_pos.y += -1 * _speed.y;
	}
	
	/*ステージ外に出ないようにする処理*/
	if (_pos.x < 0) {
		_pos.x = 0;
	}
	else if (static_cast<int>(_pos.x)+_size.x > splitscreen_W * 4) {
		_pos.x = splitscreen_W * 4-_size.x;
	}

	if (_pos.y < 0) {
		_pos.y = 0;
	}
	else if (static_cast<int>(_pos.y)+_size.y> screen_H * 4) {
		_pos.y = screen_H * 4-_size.y;
	}

	UpdateCamera();
	
	PlayFootSteps();

	if (_speed.Length()<0.1) {
		_state=PlayerState::Wait;
	}
	else if (_speed.Length() < 4.9) {
		_state = PlayerState::Walk;
	}
	else {
		_state = PlayerState::Run;
	}

	if (abs(_lastDir.x)>abs(_lastDir.y)) {
		if (_lastDir.x >= 0) {
			_direction = PlayerDirection::Right;
		}
		else {
			_direction = PlayerDirection::Left;
		}
	}
	else {
		if (_lastDir.y >= 0) {
			_direction = PlayerDirection::Down;
		}
		else {
			_direction = PlayerDirection::Up;
		}
	}
}

void Player::ChangePosition(Vector2 pos) {
	_pos = pos;
	auto&& rendercamera = _mode.GetSplitWindow()[_playerNum]->GetCamera();
	rendercamera->SetPosition(_pos);
}

void Player::UpdateCamera() {
	/*フレームアウトした際にカメラを動かす処理*/
	auto&& rendercamera = _mode.GetSplitWindow()[_playerNum]->GetCamera();
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
	else if (renderposition.y > screen_H && _dir.y > 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::DOWN);
	}
}

void Player::PlayFootSteps() {
	if (_movable) {
		double speed = _dir.Length();
		if (speed > 0 && speed <= 0.98) {
			if (_game.GetFrameCount() % 25 == 0) {
				PlaySoundMem(SoundServer::Find("PlayerWalk"), DX_PLAYTYPE_BACK);
			}
		}
		else if (speed > 0.98) {
			if (_game.GetFrameCount() % 15 == 0) {
				PlaySoundMem(SoundServer::Find("PlayerRun"), DX_PLAYTYPE_BACK);
			}
		}
	}
}

bool Player::IsHitActor() {



	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::Enemy|| actor->GetType() == Type::Server) {
			if (Intersect(_collision, actor->GetCollision())) {
			return true;
			}
		}
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() != Gimmick::GimmickType::Teleporter) {
				if (Intersect(_collision, actor->GetCollision())) {
					return true;
				}
			}
		}
	}
	return false;
}

void Player::CheckDamage() {
	--_invincibleTime;

	if (_invincibleTime < 0) {
		_invincibleTime = 0;
	}
	if (_invincibleTime == 0) {
		for (auto&& actor : _mode.GetActorServer().GetObjects()) {
			if (actor->GetType() == Type::Explode) {
				if (Intersect(_collision, actor->GetCollision())) {
					TakeDamage();
					_invincibleTime = 90;
				}
			}
		}
	}
}

void Player::Action() {
	/*子クラスにてプレイヤーごとの固有アクション設定*/
}

void Player::StandardRender(int windowNum,Vector2 window_pos,Vector2 camera_pos){
	
	
	if (_mode.GetBlindFlag() && windowNum != _playerNum) {
		return;
	}


	std::vector<int> cg = _cg[{_state, _direction}];
	if (_state == PlayerState::Set|| _state == PlayerState::Shoot) {
		DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x) - (_size.y/2),
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y) - (_size.y / 2)*0.6,
			static_cast<int>(_pos.x + window_pos.x - camera_pos.x) - (_size.y / 2)+_size.y*1.5,
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y) - (_size.y / 2)*0.6+_size.y*1.5, cg[_animNo], 1);
		++_animNo;
		if (_animNo >= cg.size()) {
			_animNo = cg.size() - 1;
		}
	}
	else {
			DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x) - (_size.y / 2),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y) - (_size.y / 2)*0.6,
				static_cast<int>(_pos.x + window_pos.x - camera_pos.x) - (_size.y / 2) + _size.y*1.5,
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y) - (_size.y / 2)*0.6 + _size.y*1.5,
				cg[_game.GetFrameCount() % cg.size()], 1);


	}
	
}

void Player::UpdateCollision() {
	_collision.min = _pos;
	_collision.max = _pos + _size;
}

void Player::TakeDamage() {
	--_hp;
	if (_hp <= 0) {
		_mode.GameOver();
	}
}

void Player::Heal() {
	++_hp;
	if (_hp > _hpMAX) {
		_hp = _hpMAX;
	}
}

void Player::TakeAmmo() {
	++_bullet;
}

void Player::Checkteleport() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::Teleporter) {
				if (Intersect(_collision, actor->GetCollision())) {
					auto teleport = dynamic_cast<teleporterIn&>(*actor);
					auto id = teleport.GetteleportID();
					if (teleport.GetRandomFlag()) {
						auto data = _mode.GetMapChips()->GetteleporterOutData();
						std::vector<Vector2> positions;
						for (auto&& pair : data) {
							if (pair.second.second) {
								positions.push_back(pair.second.first);
							}
						}
						if (positions.size() != 0) {
							_pos = positions[_game.GetFrameCount() % positions.size()];
						}
					}
					else {
						_pos = _mode.GetMapChips()->GetteleporterOutData()[id].first;
					}
					Init();
				}
			}
		}
	}
}

void Player::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	//デバッグ用座標表示

	_collision.Draw2(stageNum, window_pos, camera_pos);
	std::stringstream ss;
	ss << "HP" << _hp << "\n";
	if (_playerNum == 0) {
		ss << "弾薬" << _bullet << "\n";
	}

	ss << "_collision.max.x" << _collision.max.x << "\n";
	ss << "_collision.max.y" << _collision.max.y << "\n";
	ss << "チャージ" << _charge << "\n";
	ss << "方向" << _dir.x <<"  "<<_dir.y << "\n";
	ss << "プレイヤー" << _roomPosition.x<<","<<_roomPosition.y << "\n";
	DrawString(50 + _playerNum * 960, 100, ss.str().c_str(), GetColor(255, 0, 255));
}