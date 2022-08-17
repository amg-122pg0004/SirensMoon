#pragma once
#include "Effect.h"

class FX_Boom :public Effect {
	public:
		FX_Boom(Game& game,ModeGame& mode,const Vector2& pos, int startTime);
		virtual void Easing(int elapsed) override;
	private:
};