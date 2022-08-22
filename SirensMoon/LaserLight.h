#pragma once
#include "LightBase.h"

class Game;
class ModeGame;
class Actor;

class LaserLight :public LightBase {
public:
	LaserLight(Game&, ModeGame&, Actor&);
	void Update()override;
private:
};
