/*****************************************************************//**
 * \file   FX_HeadButt.h
 * \brief  �{�X�����˂��U���������̃G�t�F�N�g
 * 
 * \author �y�������Y
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