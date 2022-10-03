#include "SearchInfo.h"
#include "ModeGame.h"
#include "Game.h"
class SplitWindow;

SearchInfo::SearchInfo(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size }, _timer{ 0 }
{
	_visible = true;
	if (_window.GetWindowNo() == 0) {
		_cg = ImageServer::LoadGraph("resource/UI/Info/SerchInfoA.png");
		_cg2 = ImageServer::LoadGraph("resource/UI/Info/SerchInfoA2.png");
	}
	else {
		_cg = ImageServer::LoadGraph("resource/UI/Info/SerchInfoB.png");
		_cg2 = ImageServer::LoadGraph("resource/UI/Info/SerchInfoB2.png");
	}

}

void SearchInfo::Update() {
	if (!_visible) {
		return;
	}
	++_timer;
}

void SearchInfo::Render() {
	if (_visible) {
		if (_timer < 121) {
			int sizey{ 0 };
			if (_timer < 60) {
				sizey = _timer * 50;
			}
			else {
				sizey = (121 - _timer) * 50;
			}
			sizey = Math::Clamp(sizey, 0, 210);
			DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y - sizey / 2),
				static_cast<int>(_pos.x + splitscreen_W), static_cast<int>(_pos.y + sizey / 2), _cg, 1);
		}
		else {
			DrawExtendGraph(static_cast<int>(_pos.x + splitscreen_W - 290), 160,
				static_cast<int>(_pos.x + splitscreen_W - 290 +270), 160 + 114, _cg2, 1);
		}
	}
}