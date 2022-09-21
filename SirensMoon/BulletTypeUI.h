#pragma once
#include "UIBase.h"

class SplitWindow;

class BulletTypeUI :public UIBase {
public:
	BulletTypeUI(Game&, ModeBase&, SplitWindow& window, Vector2 pos, Vector2 size);

	Type GetType() override{ return UIBase::Type::BulletType; }

	void Update() override;
	void Render() override;

private:
	bool _bulletType;

	int _cg_red,_cg_green;

};
