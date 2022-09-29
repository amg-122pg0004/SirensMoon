/*****************************************************************//**
 * \file   FX_Teleport.h
 * \brief  テレポートエフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_TeleportIN1 :public Effect {
public:
	FX_TeleportIN1(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};

class FX_TeleportIN2 :public Effect {
public:
	FX_TeleportIN2(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};

class FX_TeleportOUT1 :public Effect {
public:
	FX_TeleportOUT1(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};

class FX_TeleportOUT2 :public Effect {
public:
	FX_TeleportOUT2(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};
