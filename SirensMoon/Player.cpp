#include "Player.h"
#include "ImageServer.h"

Player::Player(Game& game,int playernum)
	:Actor{ game }, _speed{ 5 }, _playerNum{playernum}
	,_dirX{0},_dirY{0}
{
	 _inputManager = _game.GetInputManager();
	 
	 _cg_up = ImageServer::LoadGraph("resource/player/up.png");
	 _cg_side = ImageServer::LoadGraph("resource/player/side.png");
	 _cg_down = ImageServer::LoadGraph("resource/player/down.png");

	 _pos = { 50,50 };
}

void Player::Update() {

	_collision.min = _pos;
	_collision.max = { _pos.x + 48,_pos.y + 48 };


	if (_inputManager->CheckInput("UP", 'h', _playerNum)) {
		_dirY = 1;
		_state = State::UP;
	}
	else if (_inputManager->CheckInput("DOWN", 'h', _playerNum)) {
		_dirY = -1;
		_state = State::DOWN;
	}
	else {
		_dirY = 0;
	}

	if (_inputManager->CheckInput("LEFT", 'h', _playerNum)) {
		_dirX = -1;
		_state = State::LEFT;
	}
	else if (_inputManager->CheckInput("RIGHT", 'h', _playerNum)) {
		_dirX = 1;
		_state = State::RIGHT;
	}
	else {
		_dirX = 0;
	}

	IsHitMapChip(_dirX, _dirY) {
		return 0;
	}
	
}

int Player::IsHitMapChip(int dirX,int dirY) {

}


void Player::Render(Vector2 window_pos,Vector2 camera_pos){
	switch (_state) {
		case State::UP:
			DrawGraph(static_cast<int>(_pos.x+window_pos.x-camera_pos.x),
				static_cast<int>(_pos.y+window_pos.y-camera_pos.y), _cg_up, 0);
			break;
		case State::DOWN:
			DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_down, 0);
			break;
		case State::LEFT:
			DrawTurnGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_side, 0);
			break;
		case State::RIGHT:
			DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_side, 0);
			break;
	}
}
