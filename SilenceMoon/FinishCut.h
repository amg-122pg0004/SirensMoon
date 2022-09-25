#pragma once
#include "UIBase.h"
#include "Easing.h"
class Game;
class ModeBase;
class SplitWindow;
class FinishCut :public  UIBase{
public:
	FinishCut(Game&, ModeBase&,SplitWindow& window, Vector2 pos, Vector2 size);
	void Update()override;
	void Render()override;
	Type GetType()override { return Type::FinishCut; }

	void TargetKillEvent() override;
private:
	bool _visible2;
	int _lifetime;
	EasingMode _easing;
	int _startTime;
	std::vector<int> _cgBlood;
	int _cg_screen;
	int _alpha;
	int _elapsed;
};
