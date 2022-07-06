#include "Darkness.h"
#include "ActorServer.h"
#include "ImageServer.h"

Darkness::Darkness(Game& game) :_game{ game }, _cg{ -1 }, _alphaHandle{-1} {
	_cg = ImageServer::LoadGraph("resource/Light/Light_3.png");
}

int Darkness::MakeDarkness() {
	_alphaHandle = MakeScreen(screen_W, screen_H, 1);
	return _alphaHandle;
}

void Darkness::Update() {
	SetDrawScreen(_alphaHandle);
	DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
	for (auto&& actor : _game.GetActorServer()->GetObjects()) {
		if (actor->GetType() == Actor::Type::Light) {
			DrawGraph(actor->GetPosition().x, actor->GetPosition().y, _cg, 1);
		}
	}
}

void Darkness::DeleteDarkness() {
	DeleteMaskScreen();
}