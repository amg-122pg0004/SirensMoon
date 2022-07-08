#include "Light.h"

Light1::Light1(Game& game, Actor& owner) : _owner{ owner }, Actor{ game }//, _lifetime{ 180 }
 {
	_pos = { 0,0 };
}

void Light1::Update() {

	_pos = _owner.GetPosition();
	/*--_lifetime;
	if (_lifetime < 0) {
		_dead = true;
	}
	*/
}

Light2::Light2(Game& game, Actor& owner) : _owner{ owner }, Actor{ game }//, _lifetime{ 180 }
{
	_pos = { 0,0 };
}

void Light2::Update() {

	_pos = _owner.GetPosition();
	/*--_lifetime;
	if (_lifetime < 0) {
		_dead = true;
	}
	*/
}

