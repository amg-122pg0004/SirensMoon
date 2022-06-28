/*****************************************************************//**
 * \file   Actor.h
 * \brief  �A�N�^�[�i��ʂɕ\������镨�́j�̐e�N���X�ł��B
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include "ActorServer.h"
#include "Math.h"

class Game;

class Actor{
	public:

		enum class Type {
			Actor,
			Player,
			Enemy,
			Bullet
		};
		Actor(Game& game);
		~Actor();

		virtual void Update();
		virtual void Render();
		virtual bool IsDead() { return _dead; }
		virtual void Dead() { _dead = true; }

	protected:
		Game& _game;
		Vector2 _pos;
		bool _dead;

};

