#include "ServerMachine.h"
#include "ImageServer.h"
#include "Game.h"
#include "ModeBase.h"

ServerMachine::ServerMachine(Game& game, ModeBase& mode, Vector2 pos, int dir)
	:Actor(game, mode), _dir{ dir }
{
	_accessArea.min = {0,0};
	_accessArea.max = { 0,0 };
	_cg_up = ImageServer::LoadGraph("resource/Server/up.png");
	_cg_right = ImageServer::LoadGraph("resource/Server/right.png");
	_cg_down = ImageServer::LoadGraph("resource/Server/down.png");
	_cg_left = ImageServer::LoadGraph("resource/Server/left.png");

	_pos = pos;
	
	switch (_dir) {
		case 1:
			_cg = _cg_up;
		case 2:
			_cg = _cg_right;
		case 3:
			_cg = _cg_down;
		case 4:
			_cg = _cg_left;
	}
	int x, y;
	GetGraphSize(_cg,&x,&y);
	_size = { static_cast<double>(x),static_cast<double>(y) };
	_collision.min = _pos;
	_collision.max = _pos + _size;

	switch (_dir) {
		case 1:
			_accessArea.min = { _pos.x ,_pos.y - 10 };
			_accessArea.max = { _pos.x + _size.x , _pos.y + _size.y };
		case 2:
			_accessArea.min = { _pos.x + _size.x,_pos.y };
			_accessArea.max = { _pos.x + _size.x + 10,_pos.y + _size.y };
		case 3:
			_accessArea.min = { _pos.x,_pos.y + _size.y };
			_accessArea.max = { _pos.x + _size.x,_pos.y + _size.y + 10 };
		case 4:
			_accessArea.min = { _pos.x - 10,_pos.y };
			_accessArea.max = { _pos.x,_pos.y + _size.y };
	}
	
}


void ServerMachine::Update() {
	
}