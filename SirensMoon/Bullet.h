/*****************************************************************//**
 * \file   Bullet.h
 * \brief  �v���C���[�����˂���e�e
 * 
 * \author amg
 * \date   July 2022
 *********************************************************************/
#pragma once
#include "Player.h"
#include "Light.h"
class Game;

class Bullet:public Actor {
	public:
		Bullet(Game& game, ModeBase& mode,Vector2 pos,Vector2 dir);
		~Bullet();
		void Update()override;
		void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

		Type GetType() override { return Type::Bullet; }

	private:
		int _cg;
		int _speed;
		Vector2 _dir;//<�e�e�̔��ĕ���

		std::unique_ptr<Light2> _light;
		int _lifetime;
};
