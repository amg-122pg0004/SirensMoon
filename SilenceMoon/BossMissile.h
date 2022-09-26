/*****************************************************************//**
 * \file   BossMissile.h
 * \brief  �{�X�����˂���U���~�T�C��
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Actor.h"
#include <random>

class BossMissile :public Actor {
public:
	BossMissile(Game& game, ModeGame& mode, Vector2 pos);
	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
	Type GetType()override { return Type::BossMissile; }
	bool CheckOverlapActor(Actor& actor);
	bool CheckCheckCrossBullet(Actor& actor);
	double GetAngle() { return _angle; }

private:
	class HitBox {
	public:
		Vector2 pos1, pos2, pos3, pos4;//<�G���_�����O���E�A�����E
	};
	Vector2 GetForward() const { return { std::cos(_angle), std::sin(_angle) }; }
	void HitActor();
	void Move();
	void UpdateCollision();
	double _angle;
	Actor* _player2;
	double _speed;
	Vector2 _room;
	HitBox _hitbox;
	std::random_device seed_gen;
	std::mt19937 engine{ seed_gen() };
	std::uniform_int_distribution<> rand2{ 1,2 };
};
