#pragma once
#include "LightBase.h"

class Game;
class ModeGame;
class Actor;

class LinkLight :public LightBase {
public:
	LinkLight(Game& game, ModeGame& mode, Actor& owner,Vector2 goal);
	void Update()override;
private:
	double _speed;
	Vector2 _goal;
};