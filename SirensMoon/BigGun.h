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

	void SetAccesible() { _accessible = true; }

private:

	bool _accessible;//<アクセス可能
};