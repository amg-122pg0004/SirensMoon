#pragma once
#include "Effect.h"

class FX_BossFire :public Effect {
public:
	FX_BossFire(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};