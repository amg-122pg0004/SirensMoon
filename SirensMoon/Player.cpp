#include "Player.h"
#include "ImageServer.h"

Player::Player(Game& game,int playernum) :Actor{ game }, _speed{ 5 }, _playerNum{playernum} {
	 _inputManager = _game.GetInputManager();

	 _cg_up = ImageServer::LoadGraph("resource/player/up.png");
	 _cg_side = ImageServer::LoadGraph("resource/player/side.png");
	 _cg_down = ImageServer::LoadGraph("resource/player/down.png");

}

void Player::Update() {
	if (_inputManager->CheckInput("UP", 'h', _playerNum)) {
		_pos.y = _pos.y - _speed;
		_state = State::UP;
	}
	if (_inputManager->CheckInput("DOWN", 'h', _playerNum)) {
		_pos.y = _pos.y + _speed;
		_state = State::DOWN;
	}
	if (_inputManager->CheckInput("LEFT", 'h', _playerNum)) {
		_pos.x = _pos.x - _speed;
		_state = State::LEFT;
	}
	if (_inputManager->CheckInput("RIGHT", 'h', _playerNum)) {
		_pos.x = _pos.x + _speed;
		_state = State::RIGHT;
	}
}

void Player::Render(){
	switch (_state) {
		UP:
		DrawGraph(_pos.x, _pos.y, _cg_up, 0);
			break;
		DOWN:
			DrawGraph(_pos.x, _pos.y, _cg_down, 0);
			break;
		LEFT:
			DrawTurnGraph(_pos.x, _pos.y, _cg_side, 0);
			break;
		RIGHT:
			DrawGraph(_pos.x, _pos.y, _cg_side, 0);
			break;
	}
}
