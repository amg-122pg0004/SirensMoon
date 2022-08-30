#include "BulletTypeUI.h"
#include "ModeBase.h"
#include "PlayerA.h"

BulletTypeUI::BulletTypeUI(Game& game, ModeBase& base, Vector2 pos, Vector2 size)
	:UIBase(game,base,pos,size),_bulletType{false}
{
	_visible = true;
	_cg_red = ImageServer::LoadGraph("resource/UI/BulletType/red.png");
	_cg_green = ImageServer::LoadGraph("resource/UI/BulletType/green.png");
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

}

