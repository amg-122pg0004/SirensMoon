#pragma once
#include "UIBase.h"
#include "Math.h"
#include <memory>
class SplitWindow;
class Game;
class ModeBase;
class InputManager;

class PauseInfoA :public UIBase {
public:
	PauseInfoA(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size);
	Type GetType() { return Type::PauseInfoA; }
	void Update() override;
	void Render() override;
private:
};

class PauseInfoB :public UIBase {
public:
	PauseInfoB(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size);
	Type GetType() { return Type::PauseInfoB; }
	void Update() override;
	void Render() override;
private:
};
