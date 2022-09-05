/*****************************************************************//**
 * \file   ModeBase.cpp
 * \brief  ���[�h�̐e�N���X�ł��B
 * 
 * \author �y�������Y
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

// �X�V
void ModeBase::Update() {
}

// �`��
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
