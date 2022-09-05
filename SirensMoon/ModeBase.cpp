/*****************************************************************//**
 * \file   ModeBase.cpp
 * \brief  モードの親クラスです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "ModeBase.h"
#include "Game.h"

ModeBase::ModeBase(Game& game)
	: _game(game)
	, _dead(false)
	,_actorServer{*this}
	,_makedNextMode{false}
{
}

ModeBase::~ModeBase()
{
	_actorServer.Clear();
}

// 更新
void ModeBase::Update() {
}

// 描画
void ModeBase::Render() {
}

void ModeBase::Debug() {

}

void ModeBase::NextMode() {
	if (!_makedNextMode) {
		_makedNextMode = true;
		_game.NextMode();
	}
}
