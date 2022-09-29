/*****************************************************************//**
 * \file   FX_Thunder.cpp
 * \brief  雷エフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "FX_Thunder.h"
#include "Easing.h"

FX_Thunder::FX_Thunder(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(120);
	ImageServer::LoadDivGraph("resource/Effect/thunder.png",120, 8, 15, 200, 150, _cg.data());
	_zoom = 2.0;
	_lifeTime = 120 ;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_Thunder::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}


FX_ThunderRing::FX_ThunderRing(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(16);
	ImageServer::LoadDivGraph("resource/Effect/thunder2.png", 16, 8, 2, 480, 270, _cg.data());
	_zoom = 2.0;
	_lifeTime = 20;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_ThunderRing::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}
