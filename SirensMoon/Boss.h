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
	/*グラフィックハンドル*/
	std::map < State, std::vector<int>> _cg;
	/*アニメーション番号*/
	int _animNo;
	double _scale;
	double _angle;
	/*プレイヤー参照*/
	Actor* _player1;
	Actor* _player2;
	State _state;
	bool _backlayer;//true時は背景に描画
	bool _visible;

	bool _phase2;//<trueでボスフェイズ2

	Vector2 _startPos;
	int _hp;
	double _speed;
	Vector2 _size2;//<巨大な状態のサイズ

	bool  _invincible;//<trueの間は無敵
	Vector2 _headbuttSize;//<ヘッドバットの攻撃範囲
	Vector2 _headSize;//<頭のくらい判定のサイズ
	AABB _hitbox;//くらい判定
	AABB _collision;

	std::random_device seed_gen;
	std::mt19937 engine{ seed_gen() };
	std::uniform_int_distribution<> rand3{ 1,3 };
	std::uniform_int_distribution<> rand2{ 1,2 };
	std::uniform_int_distribution<> rand100{ 1,100 };

	/*各stateを終えるまでの残りフレームカウント*/
	int _time;

	BossGimmickController& _controller;
};