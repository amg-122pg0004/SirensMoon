#pragma once
#include "UIBase.h"
#include "Math.h"
#include <memory>

class Game;
class ModeBase;

class RideInfo :public UIBase {
public:
	RideInfo(Game& game, ModeBase& mode, Vector2 pos, Vector2 size);
	Type GetType() { return Type::RideInfo; }
	void Update() override;
	void Render() override;
private:
	std::vector<int> _cg;
	int _animNo;
	int _loop;
};