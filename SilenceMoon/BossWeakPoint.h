#pragma once
#include "UIBase.h"
class SplitWindow;

class Game;
class ModeBase;
class Boss;

class BossWeakPoint:public UIBase {
public:
	BossWeakPoint(Game&, ModeBase&, SplitWindow& window, Vector2 pos, Vector2 size, Boss& owner, int playerno);
	Type GetType() override { return Type::FoundUI; }
	void Update()override;
	void Render()override;
private:
	int _cgRing,_cgText;
	Boss& _owner;
	int _playerno;
	double _scale;
};
