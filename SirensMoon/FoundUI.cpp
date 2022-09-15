#include "FoundUI.h"
#include "ModeGame.h"
#include "Enemy.h"

FoundUI::FoundUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size, int playerno)
	:UIBase(game, mode, pos, size), _playerno{ playerno }, _animNo{ 0 }
{
	_cg.resize(4);
	ImageServer::LoadDivGraph("resource/UI/found.png", 4, 2, 2, 90, 60, _cg.data());
}

void FoundUI::Update() {
	int detectionframe{ 0 }, detectionCompleteFrame{0};
	double findPercent{ 0.0 };
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::Enemy) {
			/*Œ©‚Â‚©‚Á‚½‚ç–Ú‚ð•\Ž¦‚·‚é‚â‚Â
			if (dynamic_cast<Enemy&>(*actor).GetChaseFlag()) {
				auto pos_col = dynamic_cast<Enemy&>(*actor).GetLastDetection()->GetCollision();
				_pos = (pos_col.min + pos_col.max) / 2;
				_visible = true;
				++_animNo;
				if (_animNo >= _cg.size() - 1) {
					_animNo = static_cast<int>(_cg.size()) - 1;
				}
			}
			*/
			detectionframe = static_cast<Enemy&>(*actor).GetDetectionFrame();
			detectionCompleteFrame = static_cast<Enemy&>(*actor).GetDetectionFrame();
			if (detectionframe < dynamic_cast<Enemy&>(*actor).GetDetectionFrame()) {
				detectionframe = dynamic_cast<Enemy&>(*actor).GetDetectionFrame();
				auto pos_col = dynamic_cast<Enemy&>(*actor).GetLastDetection()->GetCollision();
				_pos = (pos_col.min + pos_col.max) / 2;
			}
		}
	}
	if (detectionframe > 0) {
		if (detectionframe < 10) {
			_animNo = 0;
		}
		else if (detectionframe < 20) {
			_animNo = 1;
		}
		else if (detectionframe < 30) {
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
