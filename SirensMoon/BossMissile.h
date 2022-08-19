#pragma once
#include "Actor.h"

class BossMissile :public Actor {
public:
	BossMissile(Game& game, ModeGame& mode, Vector2 pos);
	void Update()override;
	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	Type GetType()override { return Type::BossMissile; }

private:
	Vector2 GetForward() const { return { std::cos(_angle), std::sin(_angle) }; }
	void HitActor();
	void Move();
	void UpdateCollision();
	double _angle;
	Actor* _player2;
	double _speed;
	Vector2 _room;
	//int _lifetime;
};
