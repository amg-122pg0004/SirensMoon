#include "LightBase.h"
#include "Actor.h"
#include "ImageServer.h"

LightBase::LightBase(Game& game, ModeBase& mode, Actor& owner) 
	:Actor{ _game,_mode }, _owner{ owner }, _angle{0},_centerPos{_pos+_size/2}
 {
	_cg = ImageServer::LoadGraph("resource/Light/Light_3.png");
}

void LightBase::Update() {
	if (_dead == false) {
		Vector2 fix = { 220,220 };
		_pos = _owner.GetPosition() - fix;
		_dead = _owner.IsDead();
	}
}

