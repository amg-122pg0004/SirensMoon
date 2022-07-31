#include "Camera.h"
#include "InputManager.h"

Camera::Camera(Game& game,ModeBase& mode,SplitWindow& sw) :
	_game{ game },
	_mode{mode},
	_splitWindow{sw},
	_pos{0,0},
	_speed{10},
	_stageSize{4,4}
 {

}

void Camera::ChangePosition(Camera::ChangeDir dir) {
	switch (dir) {

		case Camera::ChangeDir::UP :
			_pos.y = _pos.y - screen_H;
			break;
		case Camera::ChangeDir::DOWN:
			_pos.y = _pos.y + screen_H;
			break;
		case Camera::ChangeDir::LEFT:
			_pos.x = _pos.x - screen_W/2;
			break;
		case Camera::ChangeDir::RIGHT:
			_pos.x = _pos.x + screen_W/2;
			break;
	}
	if (_pos.x <= 0) {
		_pos.x = 0;
	}
	if (_pos.x >= (screen_W/2)*(_stageSize.x - 1)) {
		_pos.x = (screen_W / 2) * (_stageSize.x - 1);
	}
	if (_pos.y <= 0) {
		_pos.y = 0;
	}
	if (_pos.y >= screen_H * (_stageSize.y-1)) {
		_pos.y = screen_H * (_stageSize.y-1);
	}
}
void Camera::SetPosition(Vector2 playerpos) {
	int x= ceil(playerpos.x / (screen_W / 2))-1;
	int y = ceil(playerpos.y / screen_H)-1;
	_pos.x = x * screen_W/4;
	_pos.y = y * screen_H;
}

void Camera::Update(int playernum) {
	_inputManager = _game.GetInputManager();
	if(_inputManager->CheckInput("UP", 'h',playernum)) {
		_pos.y = _pos.y + _speed;
	}
	if (_inputManager->CheckInput("DOWN", 'h',playernum)) {
		_pos.y = _pos.y - _speed;
	}
	if (_inputManager->CheckInput("LEFT", 'h', playernum)) {
		_pos.x = _pos.x + _speed;
	}
	if (_inputManager->CheckInput("RIGHT", 'h', playernum)) {
		_pos.x = _pos.x - _speed;
	}
}
