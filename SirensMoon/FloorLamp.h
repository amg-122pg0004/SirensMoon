#pragma once
#include "Actor.h"
#include "SquareLight.h"

class FloorLamp :public Actor{
public:
	FloorLamp(Game& game, ModeGame& mode,SquareLight::SquareLightStats stats);
	Type GetType()override { return Type::FloorLamp; }
	//void ToggleSwitch();

	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	bool GetActivate() { return _activate; }

private:
	bool _activate;
};
