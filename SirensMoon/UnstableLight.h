
#pragma once
#include "LightBase.h"

class Game;
class ModeGame;
class Actor;

class ProjectionLight :public LightBase {
public:
	ProjectionLight(Game&, ModeGame&, Actor&);
	void Update()override;
private:
	double _scaleStart;
	double _scaleMax;
	int _alphaStart;
	int _alphaMax;
};