/*****************************************************************//**
 * \file   FX_Boom.cpp
 * \brief　爆発エフェクト
 *
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "FX_BossDead.h"
#include "Easing.h"

FX_BossDead::FX_BossDead(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(105);
	ImageServer::LoadDivGraph("resource/Effect/bossDead.png", 105, 5, 21, 256, 256, _cg.data());

	_zoom = 5.0;
	_lifeTime = 105;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_BossDead::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime));
}