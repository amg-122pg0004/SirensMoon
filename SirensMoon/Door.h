#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Door:public Gimmick{
public:
	Door(Game& game, ModeGame& mode, ObjectDataStructs::DoorData data);
	void Update() override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::Door; }
private:
	int _partNo;
	/*�A�N�e�B�u�A��A�N�e�B�u���摜*/
	int _cg2, _cg3;
};
