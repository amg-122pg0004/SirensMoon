/*****************************************************************//**
 * \file   FX_Chargein.h
 * \brief  プレイヤーが射撃チャージ中のエフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class Player;

class FX_Chargein :public Effect {
public:
	FX_Chargein(Game& game, ModeGame& mode, const Vector2& pos, int startTime,Player& owner);
	virtual void Easing(int elapsed) override;
	void Update()override;
private:
	/*自分を生み出した物体*/
	Player& _owner;
};