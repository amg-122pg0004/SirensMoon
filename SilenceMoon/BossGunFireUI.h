/*****************************************************************//**
 * \file   BossGunFireUI.h
 * \brief  ボスの攻撃をかわすことを促すUI
 * 
 * \author amg
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "UIBase.h"

class BossGumFireUI:public UIBase{
public:
	BossGumFireUI(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size);
	Type GetType() { return Type::BossGunFireUI; }
	void Update();
	void Render();
private:
	int _lifetime;
};
