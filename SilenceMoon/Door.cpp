#include "Door.h"

Door::Door(Game& game, ModeGame& mode, DoorData data)
	:Gimmick{game,mode,data.ID},_partNo{data.PartNo}
{
	_activate = false;
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
	_renderPriority = static_cast<int>(_pos.y + _size.y);
	if (_partNo >= 1 && _partNo <= 6||
		_partNo >= 13 && _partNo <= 18||
		_partNo >= 25 && _partNo <= 30||
		_partNo >= 37 && _partNo <= 42||
		_partNo >= 49 && _partNo <= 54||
		_partNo >= 61 && _partNo <= 66||
		_partNo >= 73 && _partNo <= 78||
		_partNo >= 85 && _partNo <= 90
		) {
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
		if (_partNo >= 31 && _partNo <= 36) {
			_collision.min = _pos;
			_collision.max = _pos + _size;
			return;
		}
		if (_partNo >= 43 && _partNo <= 48) {
			_collision.min = _pos;
			_collision.max = _pos + _size;
			return;
		}
		if (_partNo >= 55 && _partNo <= 60) {
			_collision.min = _pos;
			_collision.max = _pos + _size;
			return;
		}
		if (_partNo >= 67 && _partNo <= 72) {
			_collision.min = _pos;
			_collision.max = _pos + _size;
			return;
		}
		if (_partNo >= 79 && _partNo <= 84) {
			_collision.min = _pos;
			_collision.max = _pos + _size;
			return;
		}
		if (_partNo >= 91 && _partNo <= 96) {
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

bool Door::RecieveCall(std::vector<int> IDs, bool flag) {
	for (int id : IDs) {
		if (id == _id) {
			if (_activate != flag) {
				_activate = flag;
				if (_activate) {
					if (CheckSoundMem(SoundServer::Find("DoorOpen")) == 0) {
						PlaySoundMem(SoundServer::Find("DoorOpen"), DX_PLAYTYPE_BACK);
					}
				}
				else {
					if (CheckSoundMem(SoundServer::Find("DoorClose")) == 0) {
						PlaySoundMem(SoundServer::Find("DoorClose"), DX_PLAYTYPE_BACK);
					}
				}
			}
			return true;
		}
	}
	return false;
}
