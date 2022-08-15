#pragma once
#include "UIBase.h"

class Game;
class ModeBase;

class FoundUI :public UIBase {
public:
	FoundUI(Game&, ModeBase&, Vector2 pos, Vector2 size, int playerno);
	Type GetType() override { return Type::FoundUI; }
	void Update()override;
	void Render()override;
private:
	std::vector<int> _cg;
	int _playerno;
	int _animNo;
};
