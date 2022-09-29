/*****************************************************************//**
 * \file   FX_Boom.cpp
 * \brief  爆発エフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "FX_Boom.h"
#include "Easing.h"


FX_Boom::FX_Boom(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game,mode,pos,startTime)
{

	_cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/boom2.png", 112, 8, 14, 512, 512, _cg.data());

	_zoom = 0.5;
	_lifeTime = 60*1;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_Boom::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime ));

}

FX_Boom2::FX_Boom2(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{

	_cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/boom2.png", 112, 8, 14, 512, 512, _cg.data());

	_zoom = 2.5;
	_lifeTime = 60 * 1;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_Boom2::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(static_cast<int>(linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime)));

}

