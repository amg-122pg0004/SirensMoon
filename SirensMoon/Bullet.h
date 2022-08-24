/*****************************************************************//**
 * \file   Bullet.h
 * \brief  ÉvÉåÉCÉÑÅ[Ç™î≠éÀÇ∑ÇÈèeíe
 * 
 * \author amg
 * \date   July 2022
 *********************************************************************/
#pragma once
#include "Player.h"
#include "LightBase.h"
class Game;

class Bullet:public Actor {
	public:
		Bullet(Game& game, ModeGame& mode,Vector2 pos,Vector2 dir);
		~Bullet();
		void Update()override;
		void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
		void UpdateCollision();

		virtual Type GetType() override { return Type::Bullet; }

	private:
		int _speed;
		Vector2 _dir;//<èeíeÇÃîÚ„ƒï˚å¸
		int _lifetime;
};
