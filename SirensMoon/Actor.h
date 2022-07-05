/*****************************************************************//**
 * \file   Actor.h
 * \brief  アクター（画面に表示される物体）の親クラスです。
 * 
 * \author 土居将太郎
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
			ReconPlayer,
			Enemy,
			Bullet,
			Light
		};
		virtual Type GetType() = 0;

		Actor(Game& game);
		~Actor();

		virtual void Update();
		virtual void StandardRender(int stageNum,Vector2 window_pos, Vector2 camera_pos);
		virtual void ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos);
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

