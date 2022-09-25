#pragma once
#include "Effect.h"

class FX_HeadButt :public Effect {
public:
	FX_HeadButt(Game& game, ModeGame& mode, const Vector2& pos, int startTime);
	virtual void Easing(int elapsed) override;
private:
};