/*****************************************************************//**
 * \file   FX_Boom.h
 * \brief�@�����G�t�F�N�g
 *
 * \author �y�������Y
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