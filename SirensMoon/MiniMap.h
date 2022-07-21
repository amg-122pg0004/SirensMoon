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
	void Update() override;
	void Render() override;

private:
	std::shared_ptr<InputManager> _inputManager;
	int _cg_player;//<プレイヤーを位置画像
	int _cg_map;//<ミニマップ仮画像
	int _cg_enemy;//<敵の位置画像

};
