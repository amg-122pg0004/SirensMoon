/*****************************************************************//**
 * \file   Player.h
 * \brief �v���C���[�L����
 *
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#include "Player.h"
#include "ImageServer.h"
#include "MapChip.h"
#include <string>
#include <sstream>
#include <mutex>
#include "Bullet.h"
#include "Game.h"
#include "ModeGame.h"
#include "ProjectionLight.h"
#include "LightBase.h"
#include "SoundServer.h"

Player::Player(Game& game,ModeBase& mode,int playernum)
	:Actor{ game,mode }, _speed{ 0,0 },_speedMax{5.0}, _playerNum{playernum}
	, _dir{0,0}, _lastDir{ 1,0 }, _hp{ 3 }, _bullet{ 5 }, _movable{ 1 }, _charge{ 0 }, _cooldown{ 0 }
	,_init{false},_state{PlayerState::Wait},_direction{PlayerDirection::Right},_animNo{0}
{
	_inputManager = _game.GetInputManager();

	 Vector2 pos = dynamic_cast<ModeGame&>(_mode).GetMapChips()->GetPlayerStartPosition(_playerNum);
	 _pos = { pos.x,pos.y };
	 _stage = 1;
	 _size = { 60,90 };
	 auto light = std::make_unique<LightBase>(_game, _mode, *this);
	 _mode.GetActorServer().Add(std::move(light));
}

void Player::Init() {
	auto&& rendercamera = dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[_playerNum]->GetCamera();
	rendercamera->SetPosition(_pos);
}

void Player::Update() {

	if (_init == false) {
		Init();
		_init = true;
	}

	/*�A�i���O���͎擾*/
	_dir = _inputManager->CheckAnalogInput(_playerNum);
	_dir = _dir/1000;

	if (_dir.Length() != 0) {
		_lastDir = _dir;
		//_lastDir.Normalize();
	}

	if (_dir.Length() > 1) {
		_dir.Normalize();
	}

	Move();

	Action();

	UpdateCollision();
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
	

	/*��Q���Փˏ���*/
	/*X����*/
	_pos.x += _speed.x;
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips() ->IsHit(_stage - 1, *this)) {
		_pos.x += -1*_speed.x;
	}
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHitBarrier(_stage - 1, *this, _playerNum)) {
		_pos.x += -1 * _speed.x;
	}
	UpdateCollision();
	if (IsHitActor()) {
		_pos.x += -1 * _speed.x;
	}

	_pos.y += _speed.y;
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips() ->IsHit(_stage - 1, *this)) {
		_pos.y += -1 * _speed.y;
	}
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHitBarrier(_stage - 1, *this, _playerNum)) {
		_pos.y += -1 * _speed.y;
	}
	UpdateCollision();
	if (IsHitActor()) {
		_pos.y += -1 * _speed.y;
	}
	
	/*�X�e�[�W�O�ɏo�Ȃ��悤�ɂ��鏈��*/
	if (_pos.x < 0) {
		_pos.x = 0;
	}
	else if (static_cast<int>(_pos.x)+_size.x > screen_W / 2 * 4) {
		_pos.x = screen_W / 2 * 4-_size.x;
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

void Player::UpdateCamera() {
	/*�t���[���A�E�g�����ۂɃJ�����𓮂�������*/
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
		if (actor->GetType() != Type::PlayerA&& actor->GetType()!=Type::Item&& actor->GetType() != Type::PlayerB) {
			if (Intersect(_collision, actor->GetCollision())) {
				return true;
			}
		}
	}
	return false;
}

void Player::Action() {
	/*�q�N���X�ɂăv���C���[���Ƃ̌ŗL�A�N�V�����ݒ�*/
}

void Player::StandardRender(int stageNum,Vector2 window_pos,Vector2 camera_pos){
	std::vector<int> cg = _cg[{_state, _direction}];
	if (_state == PlayerState::Set|| _state == PlayerState::Shoot) {
		DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x) - 40,
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y) - 40, cg[_animNo], 1);
		++_animNo;
		if (_animNo >= cg.size()) {
			_animNo = cg.size() - 1;
		}
	}
	else {
		if (_stage == stageNum) {
			DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x) - 40,
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y) - 40, cg[_game.GetFrameCount() % cg.size()], 1);
		}
	}
	
}

void Player::UpdateCollision() {
	_collision.min = _pos;
	_collision.max = _pos + _size;
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
	//�f�o�b�O�p���W�\��

	_collision.Draw2(stageNum, window_pos, camera_pos);
	std::stringstream ss;
	ss << "HP" << _hp << "\n";
	if (_playerNum == 0) {
		ss << "�e��" << _bullet << "\n";
	}

	//ss << "_collision.max.x" << _collision.max.x << "\n";
	//ss << "_collision.max.y" << _collision.max.y << "\n";
	ss << "�`���[�W" << _charge << "\n";
	ss << "����" << _dir.x <<"  "<<_dir.y << "\n";
	ss << "�v���C���[" << _playerNum << "\n";
	DrawString(50 + _playerNum * 960, 100, ss.str().c_str(), GetColor(255, 0, 255));
}