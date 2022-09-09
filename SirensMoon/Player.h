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
#include <map>
#include <memory>


class Game;
class ModeGame;

class Player :public Actor {
public:
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

	Player(Game& game, ModeGame& base, int playernum);
	void Update() override;
	virtual void StandardRender(Vector2 window_pos, Vector2 camera_pos) override;
	void UpdateCamera();
	void Init();

	virtual Actor::Type GetType() override { return Type::Player; }
	int GetPlayerNum() { return _playerNum; }
	Vector2 GetDirection() { return _lastDir; }
	PlayerDirection GetGrDirection() { return _direction; }
	int GetHP() { return _hp; }

	virtual void Move();
	virtual void AnimUpdate();
	bool IsHitActor();
	/*�v���C���[�ŗL�̃A�N�V����*/
	virtual void Action();
	/*�v���C���[���m���d�Ȃ��Ă���ꍇ�̏���*/
	void PlayerOverlap();
	/*�R���W�����{�b�N�X�̈ʒu�X�V*/
	void UpdateCollision();
	/*�_���[�W�𔻒�ɐG��Ă��邩�̊m�F*/
	void CheckDamage();
	/*��_���[�W���̏���*/
	void TakeDamage(Actor::Type);
	void Heal();
	void ChangePosition(Vector2 pos);
	bool Checkteleport();
	virtual void TeleportEvent();
	void ChangeMovable(bool flag) { _movable = flag; }

	/*�n�C�h�t���O�̊m�F*/
	void UpdateHide();
	bool GetHideFlag() { return _hide; }
	bool SetHideFlag();

	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

	protected:

		std::shared_ptr<InputManager> _inputManager;

		Vector2 _dir;//<�L�����̌���
		Vector2 _lastDir;//�Ō�Ɍ������L�����̌���
		Vector2 _speed;//�ړ��̑���
		double _speedMax;//�ő呬�x
		double _accelerationRatio;//���͒l���m�[�}���C�Y�����l�̏�Z�l����������
		double _friction;//���x�����Ɏg�p����l
		bool _movable;//<True���݈̂ړ��\
		bool _stageMovable;//<True����ʊO�ւ̈ړ��𐧌�����

		bool _hide;//<true���G���猩����Ȃ�
		int _hideTime;

		int _playerNum;//<�v���C���[�̔ԍ�(0�Ȃ獶�v���C���[�A1�Ȃ�E�v���C���[�j
		int _hp,_hpMAX;//<�̗�

		int _invincibleTime;//<���G����

		/*�L�����N�^�[�̉摜�n���h��*/
		std::map <std::pair<PlayerState, PlayerDirection>, std::vector<int >> _cg;

		int _animNo;
		bool _visible;
		/*���C�g�̌��摜*/
		int _cg_light;

		bool _init;

		PlayerState _state;
		PlayerDirection _direction;

		Vector2 _teleportPosition;
		int _teleportDelay;
};