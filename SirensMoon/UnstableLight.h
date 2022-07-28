
#pragma once
#include "LightBase.h"

class Game;
class ModeBase;
class Actor;

class ProjectionLight :public LightBase {
public:
	ProjectionLight(Game&, ModeBase&, Actor&);
	void Update()override;
private:
	double _scaleStart;
	double _scaleMax;
	int _alphaStart;
	int _alphaMax;
};