#pragma once
#include "LightBase.h"

class Game;
class ModeGame;
class Actor;

class LaserLight :public LightBase {
public:
	LaserLight(Game&, ModeGame&, Actor&);
	void Update()override;
	void MaskRender(Vector2 window_pos, Vector2 camera_pos)override;
private:
	bool CheckHitEnemy(Vector2 extendPoint);
	Vector2 _extendPoint;
};