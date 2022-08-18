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
	_visible = false;
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::Enemy) {
			if (dynamic_cast<Enemy&>(*actor).GetChaseFlag()) {
				auto pos_col = dynamic_cast<Enemy&>(*actor).GetLastDetection()->GetCollision();
				_pos = (pos_col.min + pos_col.max) / 2;
				_visible = true;
				++_animNo;
				if (_animNo >= _cg.size() - 1) {
					_animNo = _cg.size() - 1;
				}
			}
		}
	}
	if (_visible == false) {
		_animNo = -1;
	}
}

void FoundUI::Render() {
	if (_visible) {
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		auto&& window = dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[_playerno];
		DrawGraph(static_cast<int>(_pos.x + window->GetWindowPos().x - window->GetCamera()->GetPosition().x - _size.x / 2),
			static_cast<int>(_pos.y + window->GetWindowPos().y - window->GetCamera()->GetPosition().y - _size.y * 1.5),
			_cg[_animNo], 1);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}
