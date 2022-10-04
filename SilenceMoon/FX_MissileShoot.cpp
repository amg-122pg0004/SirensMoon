/*****************************************************************//**
 * \file   FX_MissileShoot.h
 * \brief  ボスがミサイルを射撃した時のエフェクト
 *
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "FX_MissileShoot.h"
#include "Easing.h"

FX_MissileShoot::FX_MissileShoot(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(70);
	ImageServer::LoadDivGraph("resource/Effect/MissileShoot.png", 70, 7, 12, 220, 340, _cg.data());
	_zoom = 2.0;
	_lifeTime = 148;
	_blendMode = DX_BLENDMODE_NOBLEND;
}

void FX_MissileShoot::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime));
}