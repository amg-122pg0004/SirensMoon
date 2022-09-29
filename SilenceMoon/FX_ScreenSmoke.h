/*****************************************************************//**
 * \file   FX_ScreenSmoke.h
 * \brief  スクリーンポンプギミック起動時のエフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_ScreenSmoke :public Effect {
public:
	FX_ScreenSmoke(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};