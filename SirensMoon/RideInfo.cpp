#include "RideInfo.h"
#include "ModeGame.h"


RideInfo::RideInfo(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size },_animNo{0}, _loop{0}
{
	_visible = false;
	_cg.resize(26);
	ImageServer::LoadDivGraph("resource/UI/RideInfo.png",26,13,2,120,90,_cg.data());
}

void RideInfo::Update() {
	if (!_visible){
		return;
	}

	++_animNo;
	if (_animNo >= _cg.size()) {
		_animNo = 0;
		++_loop;
		if (_loop > 3) {
			_visible = false;
		}
	}
}

void RideInfo::Render() {
	if (_visible) {
		DrawRotaGraph(_pos.x, _pos.y+150,2.0,0.0, _cg[_animNo], 1);
	}
}