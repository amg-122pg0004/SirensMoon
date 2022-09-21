#include "WantedInfo.h"
#include "ModeGame.h"
#include "Game.h"
class SplitWindow;

WantedInfo::WantedInfo(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size },_timer{0}
{
	_visible = false;
	_cg.first = ImageServer::LoadGraph("resource/UI/WantedInfo/1.png");
	_cg.second = ImageServer::LoadGraph("resource/UI/WantedInfo/2.png");
}

void WantedInfo::Update() {
	if (!_visible) {
		return;
	}
	++_timer;
	
}

void WantedInfo::Render() {
	if (_visible) {
		if (_timer < 121) {
			int cg{ -1 };
			if (_timer % 60<30) {
				cg = _cg.second;
			}
			else {
				cg = _cg.first;
			}
			int sizey{ 0 };
			if (_timer < 60) {
				sizey = _timer * 50;
			}
			else {
				sizey = (121-_timer) * 50;
			}
			sizey=Math::Clamp(sizey,0,210);
			DrawExtendGraph(_pos.x, _pos.y - sizey /2,
				_pos.x+splitscreen_W, _pos.y + sizey /2,cg, 1);
		}
		else {
			DrawExtendGraph(_pos.x+splitscreen_W-290, 85,
				_pos.x + splitscreen_W - 290+260,85+60,_cg.second, 1);
		}

	}
}

void WantedInfo::TargetSpawnEvent(){
	_visible = true;
	_timer = 0;
}

void WantedInfo::TargetKillEvent() {
	//_visible = false;
}
