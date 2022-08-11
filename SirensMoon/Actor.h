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
#include "ImageServer.h"
#include "SoundServer.h"
class Game;

class ModeGame;
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
			RedBullet,
			GreenBullet,
			Light,
			Item,
			Server,
			Gimmick,
			Explode
		};
		virtual Type GetType() = 0;

		Actor(Game& game,ModeGame& mode);
		~Actor();
		
		virtual void Update();
		virtual void StandardRender(int stageNum,Vector2 window_pos, Vector2 camera_pos);
		virtual void ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos);
		virtual void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);
		virtual void CheckDeadOwner();
		void CheckRoomPosition();


		virtual bool IsDead() { return _dead; }
		virtual void Dead() { _dead = true; }
		virtual AABB GetCollision() { return _collision; }
		virtual Vector2 GetPosition() { return _pos; }
		virtual Vector2 GetSize() { return _size; }
		virtual Vector2 GetRoomPosition() { return _roomPosition; }
		
	protected:
		Game& _game;
		ModeGame& _mode;
		Vector2 _pos,_size;
		bool _dead;
		AABB _collision;
		int _cg;

		/*4*4に区切られたマップのどこに存在するか*/
		Vector2 _roomPosition;

		int _stage;
};