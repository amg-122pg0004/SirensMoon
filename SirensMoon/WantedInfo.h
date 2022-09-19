#pragma once
#include "UIBase.h"
#include "Math.h"

class Game;
class ModeBase;

class WantedInfo :public UIBase {
public:
	WantedInfo(Game& game, ModeBase& mode, Vector2 pos, Vector2 size);
	Type GetType() { return Type::PauseInfoA; }
	void Update() override;
	void Render() override;
	void TargetSpawnEvent()override;
	void TargetKillEvent()override;
private:
	std::pair<int, int> _cg;
	int _timer;
};