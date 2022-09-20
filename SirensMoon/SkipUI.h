#pragma once
#include "UIBase.h"
#include "Math.h"
#include <memory>

class Game;
class ModeBase;

class SkipUI :public UIBase {
public:
	SkipUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size);
	Type GetType() { return Type::SkipUI; }
	void Update() override;
	void Render() override;
	void SetVisibillity(bool flag);
private:
	std::vector<int> _cg,_cg2;
	int _animNo;
};
