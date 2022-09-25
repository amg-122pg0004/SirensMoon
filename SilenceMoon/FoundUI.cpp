#include "FoundUI.h"
#include "ModeGame.h"
#include "Enemy.h"
class SplitWindow;
FoundUI::FoundUI(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size, int playerno)
	:UIBase(game, mode, window, pos, size), _playerno{ playerno }, _animNo{ 0 }
{
	_cg.resize(4);
	ImageServer::LoadDivGraph("resource/UI/found.png", 4, 2, 2, 90, 60, _cg.data());
}

void FoundUI::Update() {
	double detectionframe{ 0 }, detectionCompleteFrame{ 0 };
	double findPercent{ 0.0 };
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::Enemy) {

			detectionframe = static_cast<Enemy&>(*actor).GetDetectionFrame();
			detectionCompleteFrame = static_cast<Enemy&>(*actor).GetDetectionCompleteFrame();
			
			if (findPercent < detectionframe / detectionCompleteFrame) {
				findPercent = detectionframe / detectionCompleteFrame;
				auto pos_col = dynamic_cast<Enemy&>(*actor).GetLastDetection()->GetCollision();
				_pos = (pos_col.min + pos_col.max) / 2;
			}
		}
	}
	if (findPercent > 0) {
		if (findPercent < 0.25) {
			_animNo = 0;
		}
		else if (findPercent < 0.5) {
			_animNo = 1;
		}
		else if (findPercent < 0.75) {
			_animNo = 2;
		}
		else {
			_animNo = 3;
		}
		_visible = true;
	}
	else {
		_visible = false;
	}

}

void FoundUI::Render() {
	if (_visible) {
		SetDrawArea(0, 0, screen_W, screen_H);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		auto&& window = dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[_playerno];
		DrawGraph(static_cast<int>(_pos.x + window->GetWindowPos().x - window->GetCamera()->GetPosition().x - _size.x / 2),
			static_cast<int>(_pos.y + window->GetWindowPos().y - window->GetCamera()->GetPosition().y - _size.y * 1.5),
			_cg[_animNo], 1);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}