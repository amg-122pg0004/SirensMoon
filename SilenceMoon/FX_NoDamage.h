/*****************************************************************//**
 * \file   FX_Thunder.h
 * \brief  �e�e���͂����ꂽ�G�t�F�N�g
 *
 * \author �y�������Y
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
