#pragma once
#include "UIBase.h"

class Game;
class ModeBase;
class Boss;

class BossWeakPoint:public UIBase {
public:
	BossWeakPoint(Game&, ModeBase&, Vector2 pos, Vector2 size, Boss& owner, int playerno);
	Type GetType() override { return Type::FoundUI; }
	void Update()override;
	void Render()override;
private:
	int _cgRing,_cgText;
	Boss& _owner;
	int _playerno;
	double _scale;
};
