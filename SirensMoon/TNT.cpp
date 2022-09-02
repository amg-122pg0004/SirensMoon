#include "TNT.h"
#include "ModeGame.h"
#include "Explode.h"

TNT::TNT(Game& game, ModeGame& mode, ObjectDataStructs::TNTData data):Gimmick(game,mode,data.ID)
{
	_activate = false;
	_pos = data.pos;
	_size = { 60,60 };
	_collision.min = _pos;
	_collision.max = _pos+_size;
	std::string No = std::to_string(data.CG);
	std::string path1{"resource/Gimmick/TNT/Off/"};
	std::string path2{ "resource/Gimmick/TNT/On/" };
	std::string ext{ ".png" };
	_cg.first = ImageServer::LoadGraph(path1 + No + ext);
	_cg.second = ImageServer::LoadGraph(path2 + No + ext);
}

void TNT::Update() {
	if (_activate) {
		auto explode = std::make_unique<Explode>(_game,_mode,_pos+(_size/2));
		_mode.GetActorServer().Add(std::move(explode));
		_dead = true;
	}
}

void TNT::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	if (!_activate) {
		int cg{ -1 };
		if(_game.GetFrameCount() % 60 < 30) {
			cg = _cg.first;
		}
		else {
			cg = _cg.second;
		}
		DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
			, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
			, cg
			, 1);
	}
}
