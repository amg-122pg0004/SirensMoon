#include "Light.h"

Light::Light(Game& game, Vector2 pos) :Actor{ game }, _lifetime{ 180 } {

	_pos = pos;
}

void Light::Update() {
	--_lifetime;
	if (_lifetime < 0) {
		_dead = true;
	}
}
