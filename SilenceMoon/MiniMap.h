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
#include <vector>

class Game;
class ModeBase;
class InputManager;
class SplitWindow;

class MiniMap :public UIBase{
public:
	MiniMap(Game&,ModeBase&, SplitWindow& window, Vector2 pos,Vector2 size);
	~MiniMap();
	Type GetType() { return Type::MiniMap; }
	void Update() override;
	void Render() override;
	void SetBossFlag();
	virtual void TargetSpawnEvent() override;

private:
	std::shared_ptr<InputManager> _inputManager;
	int _cg_base;
	std::vector<int> _cg_earth;
	int _cg_cross;
	int _cg_bar;
	int _cg_line;
	int _cg_grid;

	int _font;
	bool _boss;
	bool _noiseFlag;
	int _movieHandle;
	int _animNo;
	bool _open;
	Vector2 _visiblePos,_hidePos;
};
