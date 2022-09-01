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
	:Actor{ game,mode }, _speed{ 0,0 }, _playerNum{playernum}
	, _dir{0,0}, _lastDir{ 1,0 }, _hp{ 33 },_hpMAX{3},  _movable{1}
	,_init{false},_state{PlayerState::Wait},_direction{PlayerDirection::Right},_animNo{0}, _invincibleTime{0}
	,_stageMovable{true}
{
	_inputManager = _game.GetInputManager();
	auto data = _mode.GetMapChips()->GetPlayerData(_playerNum);
	Vector2 pos = data.StarPosition;
	_speedMax = data.SpeedMax;
	_accelerationRatio = data.Accelerate;
	_friction = data.Friction;
	_pos = { pos.x,pos.y };
	_size = { 30,60 };
	auto light = std::make_unique<LightBase>(_game, _mode, *this);
	_mode.GetActorServer().Add(std::move(light));
	auto gunlight = std::make_unique<ProjectionLight>(_game, _mode, *this);
	_mode.GetActorServer().Add(std::move(gunlight));
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
	PlayerOverlap();
	/*移動*/
	Move();
	/*テレポートに触れていたら起動*/
	Checkteleport();
	/*固有のアクション*/
	Action();
	/*敵かダメージギミックに触れていたらダメージ*/
	CheckDamage();
	/*自分の位置を確認*/
	_roomPosition=CheckRoomPosition();
}

void Player::PlayerOverlap() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA && GetType() == Type::PlayerB || actor->GetType() == Type::PlayerB && GetType() == Type::PlayerA) {
			if (Intersect(_collision, actor->GetCollision())) {
				Vector2 col1_centerpos = (_collision.min + _collision.max) / 2;
				Vector2 col2_centerpos = (actor->GetCollision().max + actor->GetCollision().min) / 2;
				Vector2 dir = col1_centerpos - col2_centerpos;
				double dx{ 0 },dy{ 0 };
				if (dir.y > 0) {
					dy = _size.y - dir.y;
				}
				else {
					dy = (_size.y + dir.y) * -1;
				}
				if (dir.x > 0) {
					dx = _size.x - dir.x;
				}
				else {
					dx = (_size.x + dir.x) * -1;
				}
				if (abs(dx) > abs(dy)) {
					dx = 0;
				}
				else {
					dy = 0;
				}
				_pos.x += dx;
				UpdateCollision();
				/*衝突するなら動かない（元の位置に戻す）*/
				if (_mode.GetMapChips()->IsHit(_collision,true) ||
					_mode.GetMapChips()->IsHitBarrier(_collision, _playerNum) ||
					IsHitActor()) {
					_pos.x -= dx;
					UpdateCollision();
				}
				_pos.y += dy;
				/*衝突するなら動かない（元の位置に戻す）*/
				UpdateCollision();
				if (_mode.GetMapChips()->IsHit(_collision,true)||
					_mode.GetMapChips()->IsHitBarrier(_collision, _playerNum)||
					IsHitActor()) {
					_pos.y -= dy;
					UpdateCollision();
				}
			}
		}
	}
}

void Player::Move() {
	if (_dir.Length() > 1) {
		_dir.Normalize();
	}
	if (_movable){
		/*入力値によって加速*/
		_speed += _dir * _accelerationRatio;

		if (_speed.Length() > _dir.Length() * _speedMax) {
			_speed -= _dir * _accelerationRatio;
		}
	}
	_speed *= _friction;
	/*障害物衝突処理*/
	/*X方向*/
	_pos.x += _speed.x;
	UpdateCollision();
	if (_mode.GetMapChips() ->IsHit(_collision,true)) {
		_pos.x += -1*_speed.x;
		_speed.x = 0;
	}
	UpdateCollision();
	if (_mode.GetMapChips()->IsHitBarrier(_collision, _playerNum)) {
		_pos.x += -1 * _speed.x;
		_speed.x = 0;
	}
	UpdateCollision();
	if (IsHitActor()) {
		_pos.x += -1 * _speed.x;
		_speed.x = 0;
	}

	_pos.y += _speed.y;
	UpdateCollision();
	if (_mode.GetMapChips() ->IsHit(_collision,true)) {
		_pos.y += -1 * _speed.y;
		_speed.y = 0;
	}
	UpdateCollision();
	if (_mode.GetMapChips()->IsHitBarrier(_collision, _playerNum)) {
		_pos.y += -1 * _speed.y;
		_speed.y = 0;
	}
	UpdateCollision();

	if (IsHitActor()) {
		_pos.y += -1 * _speed.y;
		_speed.y = 0;
	}
	
	/*ステージ外に出ないようにする処理*/
	/*画面遷移許可中*/
	if (_stageMovable) {
		if (_pos.x < 0) {
			_pos.x = 0;
			_speed.x = 0;
		}
		else if (static_cast<int>(_pos.x) + _size.x > splitscreen_W * 4) {
			_pos.x = splitscreen_W * 4 - _size.x;
			_speed.x = 0;
		}

		if (_pos.y < 0) {
			_pos.y = 0;
			_speed.y = 0;
		}
		else if (static_cast<int>(_pos.y) + _size.y > screen_H * 4) {
			_pos.y = screen_H * 4 - _size.y;
			_speed.y = 0;
		}
	}
	/*画面遷移禁止中*/
	else {
		if (_roomPosition.x*splitscreen_W < 0) {
			_pos.x = 0;
			_speed.x = 0;
		}
		else if (static_cast<int>(_pos.x) + _size.x > (_roomPosition.x + 1) *splitscreen_W) {
			_pos.x = splitscreen_W * 4 - _size.x;
			_speed.x = 0;
		}

		if (_roomPosition.y * screen_H < 0) {
			_pos.y = 0;
			_speed.y = 0;
		}
		else if (static_cast<int>(_pos.y) + _size.y > (_roomPosition.y + 1) * screen_H) {
			_pos.y = screen_H * 4 - _size.y;
			_speed.y = 0;
		}
	}


	UpdateCollision();

	UpdateCamera();
	
	PlayFootSteps();

	if (_speed.Length()<0.1) {
		_state=PlayerState::Wait;
	}
	else if (_speed.Length() < 2.8) {
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
	Vector2 renderposition = (_collision.min + _collision.max)/2 - rendercamera->GetPosition();

	if (renderposition.x < 0 && _speed.x < 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::LEFT);
	}
	else if (renderposition.x > static_cast<double>(screen_W) / 2 && _speed.x > 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::RIGHT);
	}
	if (renderposition.y < 0 && _speed.y < 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::UP);
	}
	else if (renderposition.y > screen_H && _speed.y > 0) {
		rendercamera->ChangePosition(Camera::ChangeDir::DOWN);
	}
}

void Player::PlayFootSteps() {
	if (_movable) {
		double speed = _speed.Length();
		if (speed > 0.1 && speed <= 2.5) {
			if (_game.GetFrameCount() % 25 == 0) {
				PlaySoundMem(SoundServer::Find("PlayerWalk"), DX_PLAYTYPE_BACK);
			}
		}
		else if (speed > 2.5) {
			if (_game.GetFrameCount() % 15 == 0) {
				PlaySoundMem(SoundServer::Find("PlayerRun"), DX_PLAYTYPE_BACK);
			}
		}
	}
}

bool Player::IsHitActor() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		//actor->GetType() == Type::Enemy || エネミーへの当たり判定削除
		if ( actor->GetType() == Type::Server) {
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
					TakeDamage(actor->GetType());
					_invincibleTime = 90;
				}
			}
			if (actor->GetType() == Type::BossCanon) {
				if (Intersect(_collision, actor->GetCollision())) {
					TakeDamage(actor->GetType());
					_invincibleTime = 90;
				}
			}
		}
	}
}

void Player::Action() {
	/*子クラスにてプレイヤーごとの固有アクション設定*/
}

void Player::StandardRender(Vector2 window_pos,Vector2 camera_pos){
	std::vector<int> cg = _cg[{_state, _direction}];
	if (_state == PlayerState::Set|| _state == PlayerState::Shoot) {
		DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x - (_size.y/2)),
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y - (_size.y / 2)*0.6),
			static_cast<int>(_pos.x + window_pos.x - camera_pos.x - (_size.y / 2)+_size.y*1.5),
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y - (_size.y / 2)*0.6+_size.y*1.5), cg[_animNo], 1);
		++_animNo;
		if (_animNo >= cg.size()) {
			_animNo = static_cast<int>(cg.size()) - 1;
		}
	}
	else {
			DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x - (_size.y / 2)),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y - (_size.y / 2)*0.6),
				static_cast<int>(_pos.x + window_pos.x - camera_pos.x - (_size.y / 2) + _size.y*1.5),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y - (_size.y / 2)*0.6 + _size.y*1.5),
				cg[_game.GetFrameCount() % cg.size()], 1);
	}
}

void Player::UpdateCollision() {
	_collision.min = { _pos.x,_pos.y + 20 };
	_collision.max = _pos + _size;
}

void Player::TakeDamage(Actor::Type type) {
	--_hp;
	StartJoypadVibration(DX_INPUT_PAD1,1000,600,-1);
	if (type == Type::Enemy) {
		_mode.SetPauseGame(true);
		_mode.DamageEvent();
	}
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



void Player::Checkteleport() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::Teleporter) {
				/*重なっているか*/
				if (Intersect(_collision, actor->GetCollision())) {
					/*有効で無ければ動かない*/
					if (dynamic_cast<Gimmick&>(*actor).GetActivate()) {
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
								UpdateCollision();
							}
						}
						else {
							_pos = _mode.GetMapChips()->GetteleporterOutData()[id].first;
							UpdateCollision();
						}
						Init();
					}
				}
			}
		}
	}
}

void Player::Debug(Vector2 window_pos, Vector2 camera_pos){
	//デバッグ用座標表示

	_collision.Draw2(window_pos, camera_pos);
	std::stringstream ss;
	ss << "HP" << _hp << "\n";

	ss << "_collision.max.x" << _collision.max.x << "\n";
	ss << "_collision.max.y" << _collision.max.y << "\n";

	ss << "方向" << _dir.x <<"  "<<_dir.y << "\n";
	ss << "スピード" << _speed.Length() << "\n";
	DrawString(50 + _playerNum * 960, 100, ss.str().c_str(), GetColor(255, 0, 255));
}