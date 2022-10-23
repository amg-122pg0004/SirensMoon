/*****************************************************************//**
 * \file   Boss.h
 * \brief  �{�X�G
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Actor.h"
#include <map>
#include <random>

class Player;
class BossGimmickController;

class Boss :public Actor {
public:
	Boss(Game& game, ModeGame& mode,BossGimmickController& controller, unsigned int random);
	void Update()override;
	void BackRender(Vector2 window_pos, Vector2 camera_pos)override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
	double GetScale() { return _scale; };
	double GetMapScale() { return _mapscale; }
	Type GetType()override{ return Type::Boss; }
	void CheckOverlapActor();
	void TakeDamage();
	AABB GetHitBox() { return _hitbox; }
	bool GetInvincible() { return _invincible; }
	void Dead()override;
private:
	enum class State {
		Wait,
		GunAttack1,
		GunAttack2,
		ShootMissile,
		Jump,
		Return,
		HeadButt,
		Damage,
		Thunder
	};

	void ChangeAttackState();
	void ChoiceNextAttack();
	void Wait();
	void GunAttack1();
	void GunAttack2();
	void ShootMissile();
	void HeadButt();
	void Jump();
	void DamageSequence();
	void Thunder();
	void Return();
	void UpdateCollision();
	/*�O���t�B�b�N�n���h��*/
	/*first��back�psecond��standard�p*/
	//std::map < State, std::pair<std::vector<int>, std::vector<int>>> _cg;
	std::map < State, std::vector<int>> _cg;
	/*�A�j���[�V�����ԍ�*/
	int _animNo;
	double _scale, _mapscale;
	/*�v���C���[�Q��*/
	Actor* _player1;
	Actor* _player2;

	State _state,_nextState;

	bool _backlayer;//true���͔w�i�ɕ`��
	bool _visible;

	bool _phase2;//<true�Ń{�X�t�F�C�Y2

	Vector2 _startPos;
	int _hp;
	double _speed;
	Vector2 _size2;//<����ȏ�Ԃ̃T�C�Y

	bool  _invincible;//<true�̊Ԃ͖��G
	Vector2 _headbuttSize;//<�w�b�h�o�b�g�̍U���͈�
	Vector2 _headSize;//<���̂��炢����̃T�C�Y
	AABB _hitbox;//���炢����
	AABB _collision;
	Vector2 _shootPos;

	std::random_device seed_gen;
	unsigned int _random;
	std::mt19937 engine{ _random };
	std::uniform_int_distribution<> rand3{ 1,3 };
	std::uniform_int_distribution<> rand2{ 1,2 };
	std::uniform_int_distribution<> rand100{ 1,100 };

	/*�estate���I����܂ł̎c��t���[���J�E���g*/
	int _time;

	BossGimmickController& _controller;

	int _alpha;
	bool _stop;


};