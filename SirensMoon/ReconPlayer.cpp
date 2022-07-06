#include "ReconPlayer.h"
#include "ImageServer.h"
#include "MapChip.h"
#include <string>
#include <sstream>

ReconPlayer::ReconPlayer(Game& game, int playernum):Actor{ game }, _speed{ 5 }, _playerNum{ playernum }
	, _dir{0,0}
{
	_inputManager = _game.GetInputManager();

	_cg_recon = ImageServer::LoadGraph("resource/ReconPlayer/cursor.png");

	_pos = { 200,200 };
	_stage = 1;
}

void  ReconPlayer::Update() {
	_dir = { 0,0 };
	if (_inputManager->CheckInput("UP", 'h', _playerNum)) {
		--_dir.y;
	}
	if (_inputManager->CheckInput("DOWN", 'h', _playerNum)) {
		++_dir.y;
	}
	if (_inputManager->CheckInput("LEFT", 'h', _playerNum)) {
		--_dir.x;
	}
	if (_inputManager->CheckInput("RIGHT", 'h', _playerNum)) {
		++_dir.x;
	}

	_pos = _pos + _dir * _speed;

	if (_inputManager->CheckInput("ACTION", 't', _playerNum)) {
		auto light = std::make_unique<Light>(_game,*this);
		_game.GetActorServer()->Add(std::move(light));
	}
}

void  ReconPlayer::ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_recon, 1);
}