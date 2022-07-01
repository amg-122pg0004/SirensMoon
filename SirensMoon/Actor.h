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
#include "Collision.h"

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
		virtual void Render(int stageNum,Vector2 window_pos, Vector2 camera_pos);
		virtual bool IsDead() { return _dead; }
		virtual void Dead() { _dead = true; }
		virtual AABB GetCollision() { return _collision; }
		virtual Vector2 GetPosition() { return _pos; }
		virtual Vector2 GetSize() { return _size; }

	protected:
		Game& _game;
		Vector2 _pos,_size;
		bool _dead;
		AABB _collision;

		int _stage;

};

