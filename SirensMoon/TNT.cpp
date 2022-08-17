#include "TNT.h"
#include "ModeGame.h"
#include "Explode.h"

TNT::TNT(Game& game, ModeGame& mode, int ID, Vector2 pos)
	:Gimmick{ game,mode,ID }
{
	_activate = false;
	_pos = pos;
	_size = { 30,30 };
	_collision.min = _pos;
	_collision.max = _pos+_size;

	_cg = ImageServer::LoadGraph("resource/Gimmick/TNT.png");
}

void TNT::Update() {
	if (_activate) {
		auto explode = std::make_unique<Explode>(_game,_mode,_pos+(_size/2));
		_mode.GetActorServer().Add(std::move(explode));
		_dead = true;
	}
}

void TNT::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	if (!_activate) {
		DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
			, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
			, _cg
			, 0);
	}
}
