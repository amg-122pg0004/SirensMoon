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

ProjectionLight::ProjectionLight(Game& game, ModeGame& mode, Actor& owner)
	:_scaleStart{ 0.0 }, _scaleMax{ 1.3 }
	,_alphaStart{0},_alphaMax{255}
	,LightBase{ game,mode,owner }
{	_cg = ImageServer::LoadGraph("resource/Light/Light_6.png");
	int x, y;
	GetGraphSize(_cg, &x, &y);
	_centerPos = { static_cast<double>(x/2),static_cast<double>(y) };
	_scale = _scaleStart;
	_alpha = _alphaStart;
	_pos = _owner.GetPosition()+_owner.GetSize()/2;
	auto player = dynamic_cast<Player&>(_owner);
	_angle = atan2(player.GetDirection().y, player.GetDirection().x) + (3.14 / 2.0);

}

void ProjectionLight::Update(){
	auto player =dynamic_cast<Player&>(_owner);
	_pos = _owner.GetPosition() + _owner.GetSize() / 2;
	_angle = atan2(player.GetDirection().y,player.GetDirection().x)+(3.14/2.0);

	_scale += 0.01;
	_alpha += 10;
	if (_scale > _scaleMax) {
		_scale = _scaleMax;
	}
	if (_alpha > _alphaMax) {
		_alpha = _alphaMax;
	}

	if (player.GetCharge() == 0) {
		_dead = true;
	}
}
