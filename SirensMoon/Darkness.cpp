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

void Darkness::Update(Vector2 window_pos, Vector2 camera_pos) {
	SetDrawScreen(_alphaHandle);
	DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
	for (auto&& actor : _game.GetActorServer()->GetObjects()) {
		if (actor->GetType() == Actor::Type::Light) {
			DrawGraph(actor->GetPosition().x+window_pos.x-240, actor->GetPosition().y+window_pos.y-240, _cg, 1);
		}
	}
}

void Darkness::DeleteDarkness() {
	DeleteMaskScreen();
}