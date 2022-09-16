#pragma once
#include "UIBase.h"
#include "Math.h"
#include <memory>

class Game;
class ModeBase;
class InputManager;

class ScreenEffect :public UIBase {
public:
	ScreenEffect(Game& game, ModeBase& mode, Vector2 pos, Vector2 size);
	Type GetType() { return Type::Pause; }
	void Update() override;
	void Render() override;
private:
};