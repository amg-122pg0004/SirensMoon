#pragma once
#include "UIBase.h"

class AimUI :public UIBase {
public:
	AimUI(Game&, ModeBase&, Vector2 pos, Vector2 size);
	void Update() override;
	void Render() override;
	Type GetType()override { return Type::AimUI; }
private:

	int _cg_cursor;
	Vector2 _pos_cursor;
	double _speed;

};
