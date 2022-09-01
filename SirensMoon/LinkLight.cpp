#include "LinkLight.h"
#include <math.h>

LinkLight::LinkLight(Game& game, ModeGame& mode, Actor& owner, Vector2 goal)
	: LightBase{ game,mode,owner},_speed{3.0},_goal{goal}
{
	_alpha = 255;
	_cg = ImageServer::LoadGraph("resource/Light/LinkLight.png");
	_pos = owner.GetPosition();
	_size = { 50,10 };
	_centerPos = _size / 2;
	_angle = atan2( _goal.y - _pos.y , _goal.x - _pos.x );
}

void LinkLight::Update() {

	_pos.x += cos(_angle) * _speed;
	_pos.y += sin(_angle) * _speed;

	Vector2 distance=_goal - _pos;

	if (distance.Length() < 3) {
		_dead = true;
	}
}