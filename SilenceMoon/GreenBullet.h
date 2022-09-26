/*****************************************************************//**
 * \file   Bullet.h
 * \brief  ƒvƒŒƒCƒ„[‚ª”­Ë‚·‚é—Î‚Ìe’e
 *
 * \author amg
 * \date   July 2022
 *********************************************************************/
#pragma once
#include "Bullet.h"

class GreenBullet :public Bullet {
public:
	GreenBullet(Game& game, ModeGame& mode, Vector2 pos, double dir);

	Type GetType()override { return Actor::Type::GreenBullet; }

	void Dead()override;
};
