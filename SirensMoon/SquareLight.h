#pragma once
#include "LightBase.h"
#include <string>

class Game;
class ModeGame;
class Actor;

class SquareLight :public LightBase {
public:
	struct SquareLightStats {
		std::string object{ "NULL" };
		std::string image{ "resource/Light/Light_square.png" };
		bool activate{ true };
		Vector2 pos{0,0};
		Vector2 size{100,100};
		int r{255};
		int g{255};
		int b{255};
		int alpha{100};
	};

	SquareLight(Game&, ModeGame&, Actor&, SquareLightStats);
	Type GetType()override { return Type::Light; }
	void Update()override;
	void MaskRender(Vector2 window_pos, Vector2 camera_pos)override;

private:
	int _r, _g, _b;
};