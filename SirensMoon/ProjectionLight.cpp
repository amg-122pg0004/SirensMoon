/*****************************************************************//**
 * \file   ProjectionLight.cpp
 * \brief  特定方向に放射するようなライトです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "ProjectionLight.h"
#include "ImageServer.h"
#include "Player.h"
#include <math.h>

ProjectionLight::ProjectionLight(Game& game, ModeBase& mode, Actor& owner)
	:LightBase{ game,mode,owner }
{
	_cg = ImageServer::LoadGraph("resource/Light/Light_6.png");
	_centerPos = { 40,300 };
	_scale = 1.3;
}

void ProjectionLight::Update(){
	auto player =dynamic_cast<Player&>(_owner);
	Vector2 fix = {20 ,20 };
	_pos = _owner.GetPosition()+fix;
	_angle = atan2(player.GetDirection().y,player.GetDirection().x)+(3.14/2.0);

	if (player.GetCharge() == 0) {
		_dead = true;
	}
}
