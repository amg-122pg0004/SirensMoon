/*****************************************************************//**
 * \file   FX_Boom.h
 * \brief　爆発エフェクト
 *
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_BossDead :public Effect {
public:
	FX_BossDead(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};