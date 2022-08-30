#pragma once
#include "Actor.h"
#include <map>
#include <random>

class Player;
class BossGimmickController;

class Boss :public Actor {
public:
	Boss(Game& game, ModeGame& mode,BossGimmickController& controller);
	void Update()override;
	void BackRender(Vector2 window_pos, Vector2 camera_pos)override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
	double GetScale() { return _scale; };
	Type GetType()override{ return Type::Boss; }
	void CheckOverlapActor();
	void TakeDamage();
	AABB GetHitBox() { return _hitbox; }
private:
	enum class State {
		Wait,
		GunAttack1,
		GunAttack2,
		ShootMissile,
		Jump,
		HeadButt,
		TakeDamage
	};

	void Wait();
	void GunAttack1();
	void GunAttack2();
	void ShootMissile();
	void HeadButt();
	void UpdateCollision();
	/*�O���t�B�b�N�n���h��*/
	std::map < State, std::vector<int>> _cg;
	/*�A�j���[�V�����ԍ�*/
	int _animNo;
	double _scale;
	double _angle;
	/*�v���C���[�Q��*/
	Actor* _player1;
	Actor* _player2;
	State _state;
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

	std::random_device seed_gen;
	std::mt19937 engine{ seed_gen() };
	std::uniform_int_distribution<> rand3{ 1,3 };
	std::uniform_int_distribution<> rand2{ 1,2 };
	std::uniform_int_distribution<> rand100{ 1,100 };

	/*�estate���I����܂ł̎c��t���[���J�E���g*/
	int _time;

	BossGimmickController& _controller;
};