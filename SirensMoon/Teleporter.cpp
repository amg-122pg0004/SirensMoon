#include "teleporter.h"
#include "ModeGame.h"

teleporterIn::teleporterIn(Game& game, ModeGame& mode, int ID, ObjectDataStructs::teleporterData data)
	:Gimmick(game,mode,ID)
{
	_cg = ImageServer::LoadGraph("resource/Gimmick/teleporter.png");
	_pos = data.pos;
	_size={ 40,40 };
	_teleportID = data.tereortID;
	_randomFlag = data.random;
	_collision.min = _pos-_size/2;
	_collision.max = _pos + _size-_size / 2;
}

void teleporterIn::Update(){
	
}

void teleporterIn::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x - 20),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y-20),
		_cg,0
	);
}

void teleporterIn::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(stageNum, window_pos, camera_pos);
}



teleporterOut::teleporterOut(Game& game, ModeGame& mode, int ID, Vector2 pos):  Gimmick(game, mode,ID)
{
	_pos = pos;
	_collision.min = { 0,0 };
	_collision.max = { 0,0 };
	_cg = ImageServer::LoadGraph("resource/Gimmick/teleporter.png");
}

void teleporterOut::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x - 20),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y - 20),
		_cg, 0
	);
}
