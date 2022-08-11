#include "PlayerB.h"
#include "Game.h"
#include "ModeGame.h"

PlayerB::PlayerB(Game& game, ModeGame& base, int playernum) :Player(game,base,playernum)
{
		Load();
}

void PlayerB::Load() {
	std::vector<int> handle;

	handle.resize(30);
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Wait2/back.png", 30, 5, 6, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Wait2/front.png", 30, 5, 6, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Wait2/left.png", 30, 5, 6, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Wait2/right.png", 30, 5, 6, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Right}] = handle;
	handle.resize(81);
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Walk/back.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Walk/front.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Walk/left.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Walk/right.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Right}] = handle;
	handle.resize(60);
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Run/back.png", 61, 10, 7, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Run/front.png", 61, 10, 7, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Run/left.png", 61, 10, 7, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Run/right.png", 61, 10, 7, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Right}] = handle;
	handle.resize(101);
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Wait/back.png", 101, 10, 11, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Wait/front.png", 101, 10, 11, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Wait/left.png", 101, 10, 11, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerB/Wait/right.png", 101, 10, 11, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Right}] = handle;
}

void PlayerB::Action() {
	if (_inputManager->CheckInput("ACTION", 't', _playerNum)) {
		PlaySoundMem(SoundServer::Find("PlayerOpenMap"), DX_PLAYTYPE_BACK);
		_movable = false;
	}
	else 	if (_inputManager->CheckInput("ACTION", 'r', _playerNum)) {
		_movable = true;
	}
}

void PlayerB::Move() {


	if (_movable) {
		_speed = _speed + _dir * 0.2;
	}
	auto dir = _dir;
	if (dir.Length() == 0 || !_movable) {
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
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHit(_stage - 1, *this)) {
		_pos.x += -1 * _speed.x;
	}
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHitBarrier(_stage - 1, *this, _playerNum)) {
		_pos.x += -1 * _speed.x;
	}
	UpdateCollision();
	if (IsHitActor()) {
		_pos.x += -1 * _speed.x;
	}

	_pos.y += _speed.y;
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHit(_stage - 1, *this)) {
		_pos.y += -1 * _speed.y;
	}
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHitBarrier(_stage - 1, *this, _playerNum)) {
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
	else if (static_cast<int>(_pos.x) + _size.x > screen_W / 2 * 4) {
		_pos.x = screen_W / 2 * 4 - _size.x;
	}

	if (_pos.y < 0) {
		_pos.y = 0;
	}
	else if (static_cast<int>(_pos.y) + _size.y > screen_H * 4) {
		_pos.y = screen_H * 4 - _size.y;
	}

	UpdateCamera();

	PlayFootSteps();

	if (_speed.Length() < 0.1) {
		if (_state != PlayerState::Set&&_state !=PlayerState::Wait) {
			_state = PlayerState::Set;
			_animNo = 0;
		}
		if (_animNo > 99) {
			_state = PlayerState::Wait;
		}

	}
	else if (_speed.Length() < 4.9) {
		_state = PlayerState::Walk;
	}
	else {
		_state = PlayerState::Run;
	}

	if (abs(_lastDir.x) > abs(_lastDir.y)) {
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

void PlayerB::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	Player::StandardRender(stageNum,window_pos,camera_pos);

}
