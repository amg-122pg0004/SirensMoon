#include "Darkness.h"
#include "ActorServer.h"
#include "ImageServer.h"

Darkness::Darkness(Game& game) :_game{ game }, _cg{ -1 }, _alphaHandle{-1} {
	_cg = LoadMask("resource/Light/Light_1.png");
}

int Darkness::MakeDarkness() {

	_alphaHandle = MakeScreen(screen_W, screen_H, 1);
	SetDrawScreen(_alphaHandle);
	DrawBox(0, 0, screen_W, screen_H,GetColor(0,0,0), 1);
	for (auto&& actor : _game.GetActorServer()->GetObjects()) {
		if (actor->GetType() == Actor::Type::Light) {
			DrawGraph(actor->GetPosition().x, actor->GetPosition().y, _cg,1);
		}
	}
	SetDrawScreen(DX_SCREEN_BACK);    //<•`‰ææ‰æ–Ê‚ð— ‚É‚·‚é
	return _alphaHandle;
}

void Darkness::DeleteDarkness() {
	DeleteMaskScreen();
}