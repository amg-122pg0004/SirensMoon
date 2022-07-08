/*****************************************************************//**
 * \file   Player.h
 * \brief  �v���C���[�L����
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include "Actor.h"
#include "InputManager.h"
#include "Game.h"
#include "Math.h"


class Player :public Actor {
	public:
		Player(Game& game,int playernum);
		void Update() override ;
		void StandardRender(int stageNum,Vector2 window_pos,Vector2 camera_pos) override ;
		void ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;

		Type GetType() override { return Type::Player; }
		int GetPlayerNum() { return _playerNum; }
		double GetDirX() { return _dirX; }
		double GetDirY() { return _dirY; }

		void Move();
		void CheckStress();
		void GunShoot();

		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

	private:
		std::shared_ptr<InputManager> _inputManager;

		double _dirX;//<X�����ւ̈ړ����
		double _dirY;//<Y�����ւ̈ړ����
		Vector2 _dir;//<�L�����̌���
		Vector2 _lastDir;//�Ō�Ɍ������L�����̌���
		int _speed;//�ړ��̑���
		int _playerNum;//<�v���C���[�̔ԍ�(0�Ȃ獶�v���C���[�A1�Ȃ�E�v���C���[�j

		float _stress;//<�X�g���X�Q�[�W
		float _stressSpeed;//<�X�g���X�Q�[�W���ω����鑬�x

		/*�L�����N�^�[�̉摜�n���h��*/
		int _cg_up;
		int _cg_side;
		int _cg_down;
		int _cg_recon;

};