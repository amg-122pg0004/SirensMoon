#pragma once
#include "Effect.h"

class FX_BossDead :public Effect {
public:
	FX_BossDead(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};