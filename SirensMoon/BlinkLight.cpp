/*****************************************************************//**
 * \file   BlinkLight.cpp
 * \brief  赤い点滅するライトです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "BlinkLight.h"
 /*****************************************************************//**
  * \file   BlinkLight.cpp
  * \brief  赤い点滅するライトです。
  *
  * \author 土居将太郎
  * \date   July 2022
  *********************************************************************/

#include "ImageServer.h"
#include "Enemy.h"
#include "Game.h"
#include <math.h>

BlinkLight::BlinkLight(Game& game, ModeGame& mode, Actor& owner)
	:LightBase{ game,mode,owner }
{

	_cg = ImageServer::LoadGraph("resource/Light/Light_4.png");
	int x, y;
	GetGraphSize(_cg, &x, &y);
	_centerPos = { static_cast<double>(x / 2)+100,static_cast<double>(y) +100};
	_scale = 0;

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
