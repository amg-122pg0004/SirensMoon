#include "Tereporter.h"
#include "ModeGame.h"
#include "ImageServer.h"

TereporterIn::TereporterIn(Game& game, ModeGame& mode, MapChips::TereporterData data)
	:Actor(game,mode)
{
	_cg = ImageServer::LoadGraph("resource/Gimmick/teleporter.png");
	_pos = data.pos;
	_size={ 40,40 };
	_tereportID = data.tereortID;
	_randomFlag = data.random;
	_collision.min = _pos-_size/2;
	_collision.max = _pos + _size-_size / 2;
}

void TereporterIn::Update(){
	
}

void TereporterIn::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(_pos.x+window_pos.x-camera_pos.x-20,
		_pos.y + window_pos.y - camera_pos.y-20,
		_cg,0
	);
}

void TereporterIn::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(stageNum, window_pos, camera_pos);
}



TereporterOut::TereporterOut(Game& game, ModeGame& mode, Vector2 pos):  Actor(game, mode)
{
	_pos = pos;
	_collision.min = { 0,0 };
	_collision.max = { 0,0 };
	_cg = ImageServer::LoadGraph("resource/Gimmick/teleporter.png");
}

void TereporterOut::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	DrawGraph(_pos.x + window_pos.x - camera_pos.x - 20,
		_pos.y + window_pos.y - camera_pos.y - 20,
		_cg, 0
	);
}
