#include "LightBase.h"
#include "Actor.h"

LightBase::LightBase(Game& game, ModeBase& mode, Actor& owner) 
	: _owner{ owner }, _pos{ 0,0 }, _rotation{ 0 }, _scale{0,0}
 {

}

void LightBase::Update() {

}

