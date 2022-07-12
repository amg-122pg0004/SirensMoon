#include "Light.h"
class Actor;

Light1::Light1(Game& game, ModeBase& mode, Actor& owner) : _owner{ owner }, Actor{ game,mode }
 {
	_pos = { 0,0 };

}

void Light1::Update() {

	_pos = _owner.GetPosition();
}

Light2::Light2(Game& game, ModeBase& mode, Actor& owner) : _owner{ owner }, Actor{ game,mode }
{
	_pos = { 0,0 };
}

void Light2::Update() {
	if(!_owner.IsDead())
	_pos = _owner.GetPosition();

}

