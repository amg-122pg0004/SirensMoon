#pragma once
#include "LightBase.h"

class Game;
class ModeBase;
class Actor;

class BlinkLight :public LightBase {
public:
	BlinkLight(Game&, ModeBase&, Actor&);
	void Update()override;
private:

};
