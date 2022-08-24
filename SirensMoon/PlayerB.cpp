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
	Player::Move();
	if (_speed.Length() < 0.1) {
		if (_state != PlayerState::Set&&_state !=PlayerState::Wait) {
			_state = PlayerState::Set;
			_animNo = 0;
		}
		if (_animNo > 99) {
			_state = PlayerState::Wait;
		}

	}

}

void PlayerB::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	Player::StandardRender(window_pos,camera_pos);

}
