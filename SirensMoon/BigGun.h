#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Game;
class ModeGame;
class BossGimmickController;

class BigGun :public Gimmick{
public:
	BigGun(Game& game, ModeGame& mode, BigGunData data, BossGimmickController& controller);
	Type GetType() { return Type::Gimmick; }
	GimmickType GetGimmickType() { return GimmickType::BigGun; }

	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos);
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
	void SetAccesible() { _accessible = true; }
	bool GetAccesible() { return _accessible; }
	void RidePlayer();
private:

	AABB _accessArea;

	bool _accessible;//<アクセス可能

	BossGimmickController& _controller;
};