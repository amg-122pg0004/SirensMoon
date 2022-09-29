/*****************************************************************//**
 * \file   DisplayArea.h
 * \brief  ミニマップに攻撃範囲を表示するためのオブジェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Actor.h"

class DisplayArea :public Actor {
public:
	DisplayArea(Game& game, ModeGame& mode,Actor& owner,bool left);
	Type GetType()override { return Type::DisplayArea; }
	AABB GetDisplayArea() { return _displayArea; }

	void Update()override;
private:
	AABB _displayArea;
	Actor& _owner;

	int _lifetime;
};