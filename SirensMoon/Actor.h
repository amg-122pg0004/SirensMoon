/*****************************************************************//**
 * \file   Actor.h
 * \brief  �A�N�^�[�i��ʂɕ\������镨�́j�̐e�N���X�ł��B
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/

#pragma once
#include "Math.h"
#include "Collision.h"
class Game;
class ModeBase;


class Actor{
	public:

		enum class Type {
			Actor,
			Player,
			ReconPlayer,
			Enemy,
			Bullet,
			Light,
		};
		virtual Type GetType() = 0;

		Actor(Game& game,ModeBase& mode);
		~Actor();
		
		virtual void Update();
		virtual void StandardRender(int stageNum,Vector2 window_pos, Vector2 camera_pos);
		virtual void ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos);
		virtual void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);

		virtual bool IsDead() { return _dead; }
		virtual void Dead() { _dead = true; }
		virtual AABB GetCollision() { return _collision; }
		virtual Vector2 GetPosition() { return _pos; }
		virtual Vector2 GetSize() { return _size; }
		/*���C�g�����L���Ă��邩*/
		virtual bool HaveLight() { return _validLight; }
		
	protected:
		Game& _game;
		ModeBase& _mode;
		Vector2 _pos,_size;
		bool _dead;
		AABB _collision;

		int _stage;
		bool _validLight;//<���C�g�����L���Ă��邩
		std::vector<LightBase> _lights;
};