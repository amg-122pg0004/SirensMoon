/*****************************************************************//**
 * \file   Bullet.h
 * \brief  �v���C���[�����˂���Ԃ��e�e
 *
 * \author amg
 * \date   July 2022
 *********************************************************************/
#pragma once
#include "Bullet.h"

class RedBullet :public Bullet {
public:
	RedBullet(Game& game, ModeGame& mode, Vector2 pos, double dir);

	Type GetType()override { return Actor::Type::RedBullet; }

	void Dead()override;
};
