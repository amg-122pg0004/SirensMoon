#pragma once
#include "LightBase.h"
#include <string>
#include "ObjectDataStructs.h"
class Game;
class ModeGame;
class Actor;

class SquareLight :public LightBase {
public:

	SquareLight(Game&, ModeGame&, Actor&, SquareLightStats);
	Type GetType()override { return Type::Light; }
	void Update()override;
	void MaskRender(Vector2 window_pos, Vector2 camera_pos)override;

private:
	int _r, _g, _b;
};