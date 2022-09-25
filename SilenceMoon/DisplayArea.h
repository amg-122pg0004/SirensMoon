#pragma once
#include "Actor.h"

class DisplayArea :public Actor {
public:
	DisplayArea(Game& game, ModeGame& mode,Actor& owner,bool left);
	Type GetType()override { return Type::DisplayArea; }
	AABB GetDisplayArea() { return _displayArea; }

	void Update()override;
private:
	AABB _displayArea;
	Actor& _owner;

	int _lifetime;
};