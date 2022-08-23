#pragma once
#include "Effect.h"

class Player;

class FX_Chargenow :public Effect {
public:
	FX_Chargenow(Game& game, ModeGame& mode, const Vector2& pos, int startTime, Player& owner);
	virtual void Easing(int elapsed) override;
	void Update()override;
private:
	/*自分を生み出した物体*/
	Player& _owner;
};