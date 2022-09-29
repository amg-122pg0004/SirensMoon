/*****************************************************************//**
 * \file   FX_BossFire.cpp
 * \brief  ボスの大砲攻撃エフェクト
 *
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "FX_BossFire.h"
#include "Easing.h"

FX_BossFire::FX_BossFire(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(131);
	ImageServer::LoadDivGraph("resource/Effect/fireattack.png", 131, 5, 27, 540, 480, _cg.data());

	_zoom = 4;
	_lifeTime = 60 * 1;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_BossFire::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime));
}