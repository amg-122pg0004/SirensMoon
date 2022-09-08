#include "teleporter.h"
#include "ModeGame.h"

teleporterIn::teleporterIn(Game& game, ModeGame& mode, int ID, teleporterData data)
	:Gimmick(game,mode,data.ID)
{
	_cg = ImageServer::LoadGraph("resource/Gimmick/teleporter.png");
	_pos = data.pos;
	_size={ 90,120 };
	_teleportID = data.tereortID;
	_randomFlag = data.random;
	_collision.min = _pos-_size/2;
	_collision.max = _pos + _size-_size / 2;
}

void teleporterIn::Update(){
	
}

void teleporterIn::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x - 20),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y-20),
		_cg,1
	);
}

void teleporterIn::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(window_pos, camera_pos);
	DrawFormatString(static_cast<int>(_pos.x - camera_pos.x + window_pos.y),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		GetColor(255, 0, 0), "%d", _activate);
}



teleporterOut::teleporterOut(Game& game, ModeGame& mode,TeleporterOutData data)
	:  Gimmick(game, mode,data.ID),_open{false}
{
	_pos = data.pos;
	_size = { 90,120 };
	_collision.min = { 0,0 };
	_collision.max = { 0,0 };
	_openCollision.min = _pos;
	_openCollision.min = _pos+_size;
	_cg = ImageServer::LoadGraph("resource/Gimmick/outporter.png");
	_cg2 = ImageServer::LoadGraph("resource/Gimmick/outporter1.png");
}

void teleporterOut::Update() {
	if (_open) {
		return;
	}
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::PlayerA || actor->GetType() == Actor::Type::PlayerB) {
			_open = true;
		}
	}
}
void teleporterOut::StandardRender(Vector2 window_pos, Vector2 camera_pos){
	int cg{ -1 };
	if (_open) {
		cg = _cg2;
	}
	else {
		cg = _cg;
	}
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x - 20),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y - 20),
		cg, 1
	);
}
