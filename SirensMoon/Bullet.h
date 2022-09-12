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
		Bullet(Game& game, ModeGame& mode,Vector2 pos,double dir);
		~Bullet();
		void Update()override;
		void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
		void UpdateCollision();
		void Dead()override;
		virtual Type GetType() override { return Type::Bullet; }
		Vector2 GetPrePosition() { return _prePos; }

	private:
		int _speed;
		double _dir;//<èeíeÇÃîÚ„ƒï˚å¸
		int _lifetime;
		Vector2 _prePos;
};
