#pragma once
#include "UIBase.h"
#include "Easing.h"
#include <random>

class Game;
class ModeBase;

class DamageCut :public UIBase {
public:

	DamageCut(Game&, ModeBase&, Vector2 pos, Vector2 size);
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
