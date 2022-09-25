#include "RideInfo.h"
#include "ModeGame.h"

class SplitWindow;
RideInfo::RideInfo(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size },_animNo{0}, _loop{0}
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
		DrawRotaGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y+150),2.0,0.0, _cg[_animNo], 1);
	}
}