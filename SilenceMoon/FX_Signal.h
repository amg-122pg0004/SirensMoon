/*****************************************************************//**
 * \file   FX_Signal.h
 * \brief  ボスジェネレーターの点滅する赤い光エフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_Signal :public Effect {
public:
	FX_Signal(Game& game, ModeGame& mode, const Vector2& pos, int startTime,bool longSignal);
	virtual void Easing(int elapsed) override;
private:
	int _moveLength;
	Vector2 _startPos;
};
