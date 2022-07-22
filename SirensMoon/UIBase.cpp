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

UIBase::UIBase(Game& game, ModeBase& mode, Vector2 pos, Vector2 size) 
	:_game{ game }, _mode{ mode }, _pos{ pos }, _size{ size }, _cg{ -1 }, _visible{false}
{

}

UIBase::~UIBase() {

}

void UIBase::Update() {

}

void UIBase::Render(){

}