/*****************************************************************//**
 * \file   Actor.h
 * \brief  アクターの親クラスです。抽象クラス
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#pragma once
#include "Math.h"
#include "Collision.h"
class Game;
class ModeBase;
class LightBase;


class Actor{
	public:

		enum class Type {
			Actor,
			Player,
			PlayerA,
			PlayerB,
			Enemy,
			Bullet,
			Light,
			Item,
			Server
		};
		virtual Type GetType() = 0;

		Actor(Game& game,ModeBase& mode);
		~Actor();
		
		virtual void Update();
		virtual void StandardRender(int stageNum,Vector2 window_pos, Vector2 camera_pos);
		virtual void ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos);
		virtual void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);
		virtual void CheckDeadOwner();

		virtual bool IsDead() { return _dead; }
		virtual void Dead() { _dead = true; }
		virtual AABB GetCollision() { return _collision; }
		virtual Vector2 GetPosition() { return _pos; }
		virtual Vector2 GetSize() { return _size; }
		
	protected:
		Game& _game;
		ModeBase& _mode;
		Vector2 _pos,_size;
		bool _dead;
		AABB _collision;
		int _cg;

		int _stage;
		//std::vector<LightBase> _lights;
};