/*****************************************************************//**
 * \file   FX_BulletHit.h
 * \brief  プレイヤーが打つ弾のヒットエフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Effect.h"

class FX_BulletHit :public Effect {
public:
	FX_BulletHit(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};

class FX_BulletHitRed :public FX_BulletHit {
public:
	FX_BulletHitRed(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
};

class FX_BulletHitGreen :public FX_BulletHit {
public:
	FX_BulletHitGreen(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
};
