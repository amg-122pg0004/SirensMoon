/*****************************************************************//**
 * \file   FX_HeadButt.h
 * \brief  ボスが頭突き攻撃した時のエフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_HeadButt :public Effect {
public:
	FX_HeadButt(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};