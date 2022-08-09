#pragma once
#include "Bullet.h"

class GreenBullet :public Bullet {
public:
	GreenBullet(Game& game, ModeGame& mode, Vector2 pos, Vector2 dir);

	Type GetType()override { return Actor::Type::GreenBullet; }
};
#pragma once
