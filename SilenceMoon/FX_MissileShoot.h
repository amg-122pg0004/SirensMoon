/*****************************************************************//**
 * \file   FX_MissileShoot.h
 * \brief  �{�X���~�T�C�����ˌ��������̃G�t�F�N�g
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_MissileShoot :public Effect {
public:
	FX_MissileShoot(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};