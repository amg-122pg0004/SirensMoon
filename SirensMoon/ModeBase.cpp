/*****************************************************************//**
 * \file   ModeBase.cpp
 * \brief  モードの親クラスです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "ModeBase.h"
class Game;

ModeBase::ModeBase(Game& game)
	: _game(game)
	, _dead(false)
	,_actorServer{*this}
{
}

ModeBase::~ModeBase()
{
}

// 更新
void ModeBase::Update() {
}

// 描画
void ModeBase::Render() {
}

void ModeBase::Debug() {

}

