#include "LinkLight.h"
#include "Game.h"
#include <math.h>

LinkLight::LinkLight(Game& game, ModeGame& mode, Actor& owner, Vector2 goal)
	: LightBase{ game,mode,owner},_speed{3.0},_goal{goal}
{
	_alpha = 255;
	_cg = ImageServer::LoadGraph("resource/Light/LinkLight.png");
	_pos = owner.GetPosition();
	_size = { 50,10 };
	_centerPos = {0,5};
	_angle = atan2( _goal.y - _pos.y , _goal.x - _pos.x );
}

void LinkLight::Update() {
	//if (_game.GetFrameCount() % 20 ==0 ) {
		_pos.x += cos(_angle) * _speed;
		_pos.y += sin(_angle) * _speed;
	//}


	Vector2 distance=_goal - _pos;

	if (distance.Length() < 30) {
		_dead = true;
	}
}