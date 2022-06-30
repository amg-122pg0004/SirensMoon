#include "Player.h"
#include "ImageServer.h"
#include "MapChip.h"
#include <string>
#include <sstream>

Player::Player(Game& game,int playernum)
	:Actor{ game }, _speed{ 5 }, _playerNum{playernum}
	,_dirX{0},_dirY{0}
{
	 _inputManager = _game.GetInputManager();
	 
	 _cg_up = ImageServer::LoadGraph("resource/player/up.png");
	 _cg_side = ImageServer::LoadGraph("resource/player/side.png");
	 _cg_down = ImageServer::LoadGraph("resource/player/down.png");

	 _pos = { 200,200 };
	 
}

void Player::Update() {



	_dirY = 0;
	if (_inputManager->CheckInput("UP", 'h', _playerNum)) {
		--_dirY;
		_state = State::UP;
	}
	if (_inputManager->CheckInput("DOWN", 'h', _playerNum)) {
		++_dirY;
		_state = State::DOWN;
	}

	_dirX = 0;
	if (_inputManager->CheckInput("LEFT", 'h', _playerNum)) {
		--_dirX;
		_state = State::LEFT;
	}
	if (_inputManager->CheckInput("RIGHT", 'h', _playerNum)) {
		++_dirX;
		_state = State::RIGHT;
	}

	_pos = { _pos.x + _dirX * _speed,_pos.y + _dirY * _speed };
	_pos =_pos+ _game.GetMapChips()->IsHit(*this, _dirX, _dirY);

	_collision.min = _pos;
	_collision.max = { _pos.x + 48,_pos.y + 48 };
	
}

void Player::Render(Vector2 window_pos,Vector2 camera_pos){
	std::stringstream ss;

	//ss << CheckHitMapChip(static_cast<int>(_collision.min.y) / _game.GetMapChips()->GetChipSize_H(), static_cast<int>(_collision.min.x) / _game.GetMapChips()->GetChipSize_W());
	ss << _collision.min.x;
	DrawString(500+ _playerNum*800, 100, ss.str().c_str(), GetColor(0, 0, 0));
	
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
