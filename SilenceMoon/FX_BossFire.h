/*****************************************************************//**
 * \file   FX_BossFire.h
 * \brief  �{�X�̑�C�U���G�t�F�N�g
 * 
 * \author �y�������Y
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