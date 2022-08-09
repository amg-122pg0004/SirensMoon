#pragma once
#include "Bullet.h"

class RedBullet :public Bullet {
public:
	RedBullet(Game& game, ModeGame& mode, Vector2 pos, Vector2 dir);

	Type GetType()override { return Actor::Type::RedBullet; }
};
