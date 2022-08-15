#pragma once
#include "UIBase.h"
#include "Easing.h"

class DamageCut :public UIBase {
public:

	DamageCut(Game&, ModeBase&, Vector2 pos, Vector2 size);
	void Update()override;
	void Render()override;
	void DamageEvent()override;

	Type GetType()override { return Type::DamageCut; }
private:
	int _lifetime;
	EasingMode _easing;
	int _startTime;
	double _moveX;
};
