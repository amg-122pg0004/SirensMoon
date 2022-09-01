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
#include "ModeGame.h"


Darkness::Darkness(Game& game, ModeGame& mode, SplitWindow& splitwindow) 
	:_game{ game }, _mode{ mode }, _cg{ -1 }, _alphaHandle{ -1 }, _splitWindow{ splitwindow }
{
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
			if (_splitWindow.GetInvisiblePlayer()) {
				if (_splitWindow.GetWindowNo()==0) {
					if (light.GetOwner().GetType() == Actor::Type::PlayerB) {
						continue;
					}
				}
				else {
					if (light.GetOwner().GetType() == Actor::Type::PlayerA) {
						continue;
					}
				}
			}
			light.MaskRender(_splitWindow.GetWindowPos(), _splitWindow.GetCamera()->GetPosition());
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void Darkness::DeleteDarkness() {
	DeleteMaskScreen();
}