#pragma once
#include "UIBase.h"
#include "Math.h"

class Game;
class ModeBase;
class SplitWindow;
class SearchInfo :public UIBase {
public:
	SearchInfo(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size);
	Type GetType() { return Type::PauseInfoA; }
	void Update() override;
	void Render() override;
	void TargetSpawnEvent()override;
private:
	int _cg;
	int _timer;
};