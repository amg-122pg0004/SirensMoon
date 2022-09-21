/*****************************************************************//**
 * \file   UIBase.cpp
 * \brief  UIの親クラスです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "UIBase.h"

class Game;
class ModeBase;
class SplitWindow;

UIBase::UIBase(Game& game, ModeBase& mode,SplitWindow& window, Vector2 pos, Vector2 size)
	:_game{ game }, _mode{ mode }, _pos{ pos }, _size{ size }
	,_window{window}
	, _cg{ -1 }, _visible{false}, _UIPriority{0},_dead{false}
{
}

UIBase::~UIBase() {

}

void UIBase::Update() {

}

void UIBase::Render(){

}

void UIBase::Debug() {

}
void UIBase::DamageEvent() {

}
void UIBase::TargetSpawnEvent() {

}
void UIBase::TargetKillEvent() {

}