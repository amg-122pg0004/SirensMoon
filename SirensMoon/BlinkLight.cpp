#include "BlinkLight.h"
#include "ImageServer.h"
#include "Enemy.h"
#include "Game.h"
#include <math.h>

BlinkLight::BlinkLight(Game& game, ModeBase& mode, Actor& owner)
	:LightBase{ game,mode,owner }
{

	_cg = ImageServer::LoadGraph("resource/Light/Light_4.png");
	_centerPos = { 250,250 };

}

void BlinkLight::Update() {
	_pos = _owner.GetPosition();
	int frame = _game.GetFrameCount() % 120;
	if (frame >= 0 && frame < 10) {
		_scale += 0.02;
	}
	else if (frame >= 10 && frame < 5) {
		_scale -= 0.04;
	}
	else {
		_scale = 0;
	}
}