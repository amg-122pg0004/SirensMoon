#pragma once
#include "Actor.h"

class DisplayArea :public Actor {
public:
	DisplayArea(Game& game, ModeGame& mode,Actor& owner);
	AABB GetDisplayArea() { return _displayArea; }
private:
	AABB _displayArea;
	Actor& _owner;

};