#include "BulletTypeUI.h"
#include "ModeBase.h"
#include "PlayerA.h"

class SplitWindow;

BulletTypeUI::BulletTypeUI(Game& game, ModeBase& base, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase(game,base, window, pos,size),_bulletType{false}, _visibleChangeUI{false}
{
	_visible = true;
	_cg_red = ImageServer::LoadGraph("resource/UI/BulletType/red.png");
	_cg_green = ImageServer::LoadGraph("resource/UI/BulletType/green.png");
	_cg_change = ImageServer::LoadGraph("resource/UI/BulletType/Change.png");
}

void BulletTypeUI::Update() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::PlayerA) {
			_bulletType=dynamic_cast<PlayerA&>(*actor).GetBulletType();
		}
	}
}

void BulletTypeUI::Render() {
	if (_visible) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		int cg{ -1 };
		if (_bulletType) {
			cg = _cg_green;
		}
		else {
			cg = _cg_red;
		}

		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), cg, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (_visibleChangeUI) {
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y + 180), _cg_change, 1);
	}
}

void BulletTypeUI::TargetSpawnEvent() {
	_visibleChangeUI = true;
}
void BulletTypeUI::TargetKillEvent() {
	_visibleChangeUI = false;
}