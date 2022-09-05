/*****************************************************************//**
 * \file   MiniMap.h
 * \brief  ミニマップを表示するUIです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "UIBase.h"
#include <memory>

class Game;
class ModeBase;
class InputManager;

class MiniMap :public UIBase{
public:
	MiniMap(Game&,ModeBase&,Vector2 pos,Vector2 size);
	~MiniMap();
	Type GetType() { return Type::MiniMap; }
	void Update() override;
	void Render() override;
	void SetBossFlag();

private:
	std::shared_ptr<InputManager> _inputManager;
	int _cg_map;//<ミニマップ仮画像
	int _cg_grid;

	bool _boss;
	bool _noiseFlag;
	int _prelightUp;
	int _movieHandle;
};
