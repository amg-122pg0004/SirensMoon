/*****************************************************************//**
 * \file   FX_Signal.h
 * \brief  �{�X�W�F�l���[�^�[�̓_�ł���Ԃ����G�t�F�N�g
 * 
 * \author �y�������Y
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
