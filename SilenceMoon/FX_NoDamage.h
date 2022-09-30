/*****************************************************************//**
 * \file   FX_Thunder.h
 * \brief  銃弾がはじかれたエフェクト
 *
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"


class FX_NoDamage :public Effect {
public:
	FX_NoDamage(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
	virtual void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
private:
};
