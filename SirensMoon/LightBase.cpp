#include "LightBase.h"
#include "Actor.h"
#include "ImageServer.h"

LightBase::LightBase(Game& game, ModeBase& mode, Actor& owner) :Actor{_game,_mode},_owner{owner}
 {
	_cg = ImageServer::LoadGraph("resource/Light/Light_3.png");
}

void LightBase::Update() {
	if (_dead==false) {
		_pos = _owner.GetPosition();
		_dead = _owner.IsDead();
	}
}

