/*****************************************************************//**
 * \file   FX_BossFire.h
 * \brief  ボスの大砲攻撃エフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_BossFire :public Effect {
public:
	FX_BossFire(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};