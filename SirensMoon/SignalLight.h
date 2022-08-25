#pragma once
#include "LightBase.h"

class SignalLight :public LightBase {
public:
	SignalLight(Game& game, ModeGame& mode, Actor& owner);
	void Update()override;
	void MaskRender(Vector2 window_pos,Vector2 camera_pos);
private:

};
