#pragma once
#include "ScreenEffect.h"
class SplitWindow;
class Screen_Fade :public ScreenEffect {
public:
	Screen_Fade(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size);
	void Easing(int elapsed) override;
	void Render()override;
	void SetEffect(int delayTime, int lifeTime, unsigned int color, bool feedout);
private:
	unsigned int _color;
	bool _feedout;
};
