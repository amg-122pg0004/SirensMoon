#include "BossWeakPoint.h"
#include "ModeGame.h"
#include "Boss.h"

class SplitWindow;

BossWeakPoint::BossWeakPoint(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size, Boss& owner, int playerno)
	:UIBase(game, mode, window, pos, size), _owner{owner}, _playerno{playerno}, _scale{0}
{
	_cgRing = ImageServer::LoadGraph("resource/UI/Boss/ring.png");
	_cgText = ImageServer::LoadGraph("resource/UI/Boss/text.png");
	_visible = true;
}

void BossWeakPoint::Update() {
	_pos = _owner.GetPosition();
	if (_owner.GetInvincible()) {
		_visible = false;
	}
	else {
		_visible = true;
		_scale += 0.04;
		if (_scale > 1.0) {
			_scale = 0;
		}
	}
}

void BossWeakPoint::Render() {
	if (_visible) {
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		Vector2 pos = _owner.GetPosition();
		auto&& window = dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[_playerno];
		DrawGraph(static_cast<int>(pos.x+window->GetWindowPos().x - window->GetCamera()->GetPosition().x-_size.x/2)-2,
			static_cast<int>(pos.y-85- window->GetCamera()->GetPosition().y-_size.y / 2),_cgRing , 1);
		DrawRotaGraph(static_cast<int>(pos.x + window->GetWindowPos().x - window->GetCamera()->GetPosition().x)-2,
			static_cast<int>(pos.y - 120 - window->GetCamera()->GetPosition().y), 
		_scale, 0,_cgText,1);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}