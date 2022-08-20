#pragma once
#include "Actor.h"
#include <map>
#include <random>

class Player;

class Boss :public Actor {
public:
	Boss(Game& game, ModeGame& mode);
	void Update()override;
	void BackRender(Vector2 window_pos, Vector2 camera_pos)override;
	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	double GetScale() { return _scale; };
	Type GetType()override{ return Type::Boss; }
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
	std::map < State, std::vector<int>> _cg;
	int _animNo;
	double _scale;
	double _angle;
	Actor* _player1;
	Actor* _player2;
	State _state;
	bool _backlayer;
	bool _visible;
	double _speed;
	bool  _invincible;//<true�̊Ԃ͖��G
	Vector2 _headbuttSize;//<�w�b�h�o�b�g�̍U���͈�
	Vector2 _headSize;//<���̂��炢����̃T�C�Y
	AABB _collision;

	std::random_device seed_gen;
	std::mt19937 engine{ seed_gen() };
	std::uniform_int_distribution<> rand3{ 1,3 };
	std::uniform_int_distribution<> rand2{ 1,2 };
	std::uniform_int_distribution<> rand100{ 1,100 };

	/*�J�����̈ꎞ�I�ȕϐ�*/
	int _time;
};