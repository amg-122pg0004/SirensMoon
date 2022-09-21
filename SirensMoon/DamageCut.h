#pragma once
#include "UIBase.h"
#include "Easing.h"

class Game;
class ModeBase;
class SplitWindow;

class DamageCut :public UIBase {
public:

	DamageCut(Game&, ModeBase&, SplitWindow& window, Vector2 pos, Vector2 size);
	void Update()override;
	void Render()override;
	void DamageEvent()override;

	Type GetType()override { return Type::DamageCut; }
private:
	bool _cgChange;
	int _cg2;
	int _lifetime;
	EasingMode _easing;
	int _startTime;
	double _moveX;
};
