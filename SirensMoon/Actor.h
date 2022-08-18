/*****************************************************************//**
 * \file   Actor.h
 * \brief  �A�N�^�[�̐e�N���X�ł��B���ۃN���X
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/

#pragma once
#include <memory>
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
			Explode,
			Effect,
			Boss,
			BossCanon
		};
		virtual Type GetType() = 0;

		Actor(Game& game,ModeGame& mode);
		~Actor();
		
		virtual void Update();
		virtual void StandardRender(int stageNum,Vector2 window_pos, Vector2 camera_pos);
		virtual void ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos);
		virtual void BackRender(Vector2 window_pos, Vector2 camera_pos);
		virtual void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);
		virtual void CheckDeadOwner();
		virtual void CheckRoomPosition();

		virtual bool IsDead() { return _dead; }
		virtual void Dead() { _dead = true; }
		virtual AABB GetCollision() { return _collision; }
		virtual Vector2 GetPosition() { return _pos; }
		virtual Vector2 GetSize() { return _size; }
		virtual Vector2 GetRoomPosition() { return _roomPosition; }

		int GetRenderPriority() { return _renderPriority; }

	protected:
		/*�֐��A�N�Z�X�p�̎Q��*/
		Game& _game;
		ModeGame& _mode;
		/*�A�N�^�[�̈ʒu�ƃT�C�Y*/
		Vector2 _pos,_size;
		/*True�̕����폜����t���O*/
		bool _dead;
		/*�����蔻��*/
		AABB _collision;
		/*�摜�`��p�̃n���h��*/
		int _cg;
		/*�`��D��x*/
		int _renderPriority;

		/*4*4�ɋ�؂�ꂽ�}�b�v�̂ǂ��ɑ��݂��邩*/
		Vector2 _roomPosition;

		int _stage;
};