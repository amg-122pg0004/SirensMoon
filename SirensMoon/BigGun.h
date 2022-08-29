#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Game;
class ModeGame;

class BigGun :public Gimmick{
public:
	BigGun(Game& game, ModeGame& mode, ObjectDataStructs::BigGunData data);
	Type GetType() { return Type::Gimmick; }
	GimmickType GetGimmickType() { return GimmickType::BigGun; }

	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos);
	void SetAccesible() { _accessible = true; }

private:

	AABB _accessArea;

	bool _accessible;//<アクセス可能
};