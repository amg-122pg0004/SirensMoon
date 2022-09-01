#include "Door.h"

Door::Door(Game& game, ModeGame& mode, ObjectDataStructs::DoorData data)
	:Gimmick{game,mode,data.ID},_partNo{data.PartNo}
{
	_pos = data.pos;
	_size = { 30,30 };
	_collision.min = _pos;
	_collision.max = _pos + _size;

	std::string path1{ "resource/Gimmick/door/" };
	std::string path2{ "resource/Gimmick/door2/" };
	std::string No = std::to_string(data.PartNo);
	std::string extension{ ".png" };
	_cg2 = ImageServer::LoadGraph(path1 + No + extension);
	_cg3 = ImageServer::LoadGraph(path2 + No + extension);
	_renderPriority = _pos.y + _size.y;
	if (_partNo >= 1 && _partNo <= 6) {
		_renderPriority = 200000;
	}
	if (_partNo >= 13 && _partNo <= 18) {
		_renderPriority = 200000;
	}
}

void Door::Update() {
	if (!_activate) {
		if (_partNo >= 7 && _partNo <= 12) {
			_collision.min = _pos;
			_collision.max = _pos + _size;
			return;
		}
		if (_partNo >= 19 && _partNo <= 24) {
			_collision.min = _pos;
			_collision.max = _pos + _size;
			return;
		}
	}
	_collision.min = { 0,0 };
	_collision.max = { 0,0 };

}

void Door::StandardRender(Vector2 window_pos, Vector2 camera_pos){
if (!_activate) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg2
		, 1);
}
else {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg3
		, 1);
	}
}