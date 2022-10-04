/*****************************************************************//**
 * \file   FX_Chargenow.h
 * \brief  �v���C���[���ˌ��`���[�W�������Ă��鎞�̃G�t�F�N�g
 *
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class Player;

class FX_Chargenow :public Effect {
public:
	FX_Chargenow(Game& game, ModeGame& mode, const Vector2& pos, int startTime, Player& owner);
	virtual void Easing(int elapsed) override;
	void Update()override;
private:
	/*�����𐶂ݏo��������*/
	Player& _owner;
};