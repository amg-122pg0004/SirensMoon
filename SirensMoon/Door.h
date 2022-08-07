#pragma once
#include "Gimmick.h"

class Door:public Gimmick{
public:
	Door(Game& game, ModeGame& mode, int ID, Vector2 pos);
	void Update() override;
	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::Door; }
};
