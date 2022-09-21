#pragma once
#include "UIBase.h"
#include "Math.h"
#include <memory>

class Game;
class ModeBase;
class InputManager;
class SplitWindow;

class Briefing :public UIBase {
public:
	Briefing(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size);
	Type GetType() { return Type::Briefing; }
	void Update() override;
	void Render() override;
private:
	std::shared_ptr<InputManager> _inputManager;
	std::vector<int> _cg;
	int _slideNo,_nextslideNo;
	int _slideTime, _slideTimeMax;
};