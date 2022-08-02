/*****************************************************************//**
 * \file   Darkness.cpp
 * \brief  暗闇表現用クラス
 *
 * \author 土居太郎
 * \date   July 2022
 *********************************************************************/

#include "Darkness.h"
#include "ImageServer.h"
#include "SplitWindow.h"
#include "LightBase.h"


Darkness::Darkness(Game& game, ModeBase& mode, SplitWindow& splitwindow) :_game{ game }, _mode{ mode }, _cg{ -1 }, _alphaHandle{ -1 }, _splitWindow{ splitwindow }{
	_cg = ImageServer::LoadGraph("resource/Light/Light_3.png");
	_cg2 = ImageServer::LoadGraph("resource/Light/Light_4.png");
}

int Darkness::MakeDarkness() {
	_alphaHandle = MakeScreen(screen_W, screen_H, 1);
	return _alphaHandle;
}
/**/
void Darkness::Update(Vector2 window_pos, Vector2 camera_pos) {

	SetDrawScreen(_alphaHandle);
	ClearDrawScreen();
	DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType()==Actor::Type::Light) {		
			LightBase& light = dynamic_cast<LightBase&>(*actor);
			int alpha =light.GetAlpha();
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawRotaGraph2(static_cast<int>(light.GetPosition().x + window_pos.x - _splitWindow.GetCamera()->GetPosition().x),
				static_cast<int>(light.GetPosition().y + window_pos.y - _splitWindow.GetCamera()->GetPosition().y),
				light.GetCenterPosition().x,
				light.GetCenterPosition().y,
				light.GetScale(), 
				light.GetAngle(), 
				light.GetGrHandle(), 1, 0);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void Darkness::DeleteDarkness() {
	DeleteMaskScreen();
}