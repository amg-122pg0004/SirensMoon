#include "Darkness.h"
#include "ImageServer.h"
#include "SplitWindow.h"
#include "LightBase.h"


Darkness::Darkness(Game& game,ModeBase& mode, SplitWindow& splitwindow) :_game{game},_mode { mode }, _cg{-1}, _alphaHandle{-1}, _splitWindow{splitwindow}{
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
	DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->HaveLight()==1) {
			DrawGraph(static_cast<int>(actor->GetPosition().x+window_pos.x-240.0 - _splitWindow.GetCamera()->GetPosition().x),
				static_cast<int>(actor->GetPosition().y + window_pos.y -240.0 - _splitWindow.GetCamera()->GetPosition().y), _cg, 1);
		}
		if (actor->GetType()==Actor::Type::Light) {
			/*
			auto cg=dynamic_cast<LightBase&>(*actor).GetGrHandle();
			DrawGraph(static_cast<int>(actor->GetPosition().x + window_pos.x - 240.0 - _splitWindow.GetCamera()->GetPosition().x),
				static_cast<int>(actor->GetPosition().y + window_pos.y - 240.0 - _splitWindow.GetCamera()->GetPosition().y), cg, 1);
			*/
			
			auto light = dynamic_cast<LightBase&>(*actor);
			DrawRotaGraph2(static_cast<int>(actor->GetPosition().x + window_pos.x - _splitWindow.GetCamera()->GetPosition().x),
				static_cast<int>(actor->GetPosition().y + window_pos.y - _splitWindow.GetCamera()->GetPosition().y),
				light.GetCenterPosition().x, light.GetCenterPosition().y, 1.0, light.GetAngle(), light.GetGrHandle(), 1, 0);
		}
	}	
}

void Darkness::DeleteDarkness() {
	DeleteMaskScreen();
}