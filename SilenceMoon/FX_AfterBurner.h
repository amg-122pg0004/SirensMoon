/*****************************************************************//**
 * \file   FX_AfterBurner.h
 * \brief  �~�T�C���̉��G�t�F�N�g
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class BossMissile;

class FX_AfterBurner:public Effect {
public:
	FX_AfterBurner(Game& game, ModeGame& mode, const Vector2& pos, int startTime, BossMissile& owner);
	void Update()override;
	virtual void Easing(int elapsed) override;
private:
	BossMissile& _owner;
	void CheckDeadOwner()override;
};