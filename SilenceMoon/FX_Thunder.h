/*****************************************************************//**
 * \file   FX_Thunder.h
 * \brief  ���G�t�F�N�g
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_Thunder :public Effect {
public:
	FX_Thunder(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};

class FX_ThunderRing :public Effect {
public:
	FX_ThunderRing(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};
