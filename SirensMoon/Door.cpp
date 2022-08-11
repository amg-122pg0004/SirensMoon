#include "Door.h"

Door::Door(Game& game, ModeGame& mode, int ID, Vector2 pos)
	:Gimmick{game,mode,ID}
{
	_pos = pos;
	_size = { 30,30 };
	_collision.min = _pos;
	_collision.max = _pos + _size;

	_cg = ImageServer::LoadGraph("resource/Gimmick/door.png");
}

void Door::Update() {
	if (!_activate) {
		_collision.min = _pos;
		_collision.max = _pos + _size;
	}
	else {
		_collision.min = { 0,0 };
		_collision.max = { 0,0 };
	}
}

void Door::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos){
if (!_activate) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 0);
	}
}
