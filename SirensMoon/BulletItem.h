#pragma once
#include "Actor.h"

class Game;
class ModeBase;

class BulletItem :public Actor {
	public:
		BulletItem(Game& game, ModeBase& mode);
	private:

};