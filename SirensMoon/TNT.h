#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class TNT :public Gimmick {
public:
	TNT(Game& game, ModeGame& mode,ObjectDataStructs::TNTData data);
	void Update() override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::Door; }

private:
	std::pair<int, int> _cg;
};
