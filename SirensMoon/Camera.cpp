#include "Camera.h"
#include "InputManager.h"
#include <sstream>

Camera::Camera(Game& game,SplitWindow& sw) :
	_game{ game },
	_splitWindow{sw},
	_cameraPosition{0,0},
	_speed{10}
 {
}

void Camera::Update(int playernum) {
	_inputManager = _game.GetInputManager();
	if(_inputManager->CheckInput("UP", 'h',playernum)) {
		_cameraPosition.y = _cameraPosition.y + _speed;
	}
	if (_inputManager->CheckInput("DOWN", 'h',playernum)) {
		_cameraPosition.y = _cameraPosition.y - _speed;
	}
	if (_inputManager->CheckInput("LEFT", 'h', playernum)) {
		_cameraPosition.x = _cameraPosition.x + _speed;
	}
	if (_inputManager->CheckInput("RIGHT", 'h', playernum)) {
		_cameraPosition.x = _cameraPosition.x - _speed;
	}
}

void Camera::Render(int x,int y) {
	std::stringstream ss;
	ss <<"カメラX座標"<< _cameraPosition.x << "\n";
	ss << "カメラY座標" << _cameraPosition.y << "\n";
	DrawString(x, y, ss.str().c_str(), GetColor(255,255,255));
}


