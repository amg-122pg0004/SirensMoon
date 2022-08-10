#pragma once
#include "UIBase.h"
#include "Easing.h"

class GameOverUI :public UIBase{
public:
	GameOverUI(Game&, ModeBase&, Vector2 pos, Vector2 size);
	Type GetType()override { return Type::GameOver; }

	void Update() override;

	void Render() override;

private:
	EasingMode _easing;
	int _startTime;
	double _alpha;
};
