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

class Bullet:public Actor {
	public:
		Bullet(Game& game,Vector2 pos,Vector2 dir,Actor& owner);
		~Bullet();
		void Update()override;
		void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

		Type GetType() override { return Type::Bullet; }

	private:
		int _cg;
		int _speed;
		Vector2 _dir;//<�e�e�̔��ĕ���
		Actor& _owner;
		Actor& _ref;

		//Actor& _light;
		int _lifetime;
};
