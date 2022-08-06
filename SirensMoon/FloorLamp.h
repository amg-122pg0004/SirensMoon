#pragma once
#include "Gimmick.h"
#include "SquareLight.h"

class FloorLamp :public Gimmick{
public:
	FloorLamp(Game& game, ModeGame& mode, int ID,SquareLight::SquareLightStats stats);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::FloorLamp; }

	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;


};
