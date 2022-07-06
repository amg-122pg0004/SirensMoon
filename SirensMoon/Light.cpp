#include "Light.h"

Light::Light(Game& game, Actor& owner) : _owner{ owner }, Actor{ game }//, _lifetime{ 180 }
 {
	_pos = { 0,0 };
}

void Light::Update() {

	_pos = _owner.GetPosition();
	/*--_lifetime;
	if (_lifetime < 0) {
		_dead = true;
	}
	*/
}
