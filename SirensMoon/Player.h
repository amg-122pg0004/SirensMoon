/*****************************************************************//**
 * \file   Player.h
 * \brief  �v���C���[�L����
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "Actor.h"
#include "InputManager.h"
#include "Math.h"
#include "LightBase.h"
#include <map>


class Game;
class ModeBase;

class Player :public Actor {
	public:
		Player(Game& game,ModeBase& base,int playernum);
		void Update() override ;
		void StandardRender(int stageNum,Vector2 window_pos,Vector2 camera_pos) override ;
		void UpdateCamera();
		void Init();
		void Load();

		Type GetType() override { return Type::Player; }
		int GetPlayerNum() { return _playerNum; }
		Vector2 GetDirection() { return _lastDir; }
		int GetCharge() { return _charge; }

		void Move();
		bool IsHitActor();
		void GunShoot();
		void OpenMap();
		void PlayFootSteps();
		void UpdateCollision();
		void TakeDamage();
		void Heal();
		void TakeAmmo();

		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

		/*�O���t�B�b�N�p���*/
		enum class PlayerState {
			Wait,
			Walk,
			Run,
			Set,
			Shoot
		};
		/*�O���t�B�b�N�p����*/
		enum class PlayerDirection {
			Up,
			Down,
			Left,
			Right,
		};

	private:
		std::shared_ptr<InputManager> _inputManager;

		Vector2 _dir;//<�L�����̌���
		Vector2 _lastDir;//�Ō�Ɍ������L�����̌���
		Vector2 _speed;//�ړ��̑���
		double _speedMax;//�ړ��̍ő呬
		bool _movable;

		int _playerNum;//<�v���C���[�̔ԍ�(0�Ȃ獶�v���C���[�A1�Ȃ�E�v���C���[�j
		int _hp;//<�̗�

		/*�ˌ��֌W*/
		int _bullet;//�c��̒e��
		int _charge;//�`���[�W
		int _cooldown;//�N�[���_�E��

		/*�L�����N�^�[�̉摜�n���h��*/
		std::map <std::pair<PlayerState, PlayerDirection>, std::vector<int >> _cg;

		int _animNo;

		/*���C�g�̌��摜*/
		int _cg_light;

		bool _init;

		PlayerState _state;
		PlayerDirection _direction;
};