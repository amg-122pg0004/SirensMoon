#pragma once
#include "Gimmick.h"
#include "SquareLight.h"

class FloorLamp :public Gimmick{
public:
	FloorLamp(Game& game, ModeGame& mode,SquareLightStats stats);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::FloorLamp; }
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

private:
	int _cg;
};
