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
	, _delayNextMode{20}
	, _renderPriority{0}
{
}

ModeBase::~ModeBase()
{
	_actorServer.Clear();
}

// �X�V
void ModeBase::Update() {
	--_delayNextMode;
}

// �`��
void ModeBase::Render() {

}

void ModeBase::Debug() {

}

void ModeBase::NextMode() {
	if (!_makedNextMode&&_delayNextMode<0) {
		_makedNextMode = true;
		_game.NextMode();
	}
}

void ModeBase::CallPlayStage1() {
	if (!_makedNextMode && _delayNextMode < 0) {
		_makedNextMode = true;
		_game.PlayStage1();
	}
}

void ModeBase::CallPlayStage2() {
	if (!_makedNextMode && _delayNextMode < 0) {
		_makedNextMode = true;
		_game.PlayStage2();
	}
}

void ModeBase::CallPlayStage3() {
	if (!_makedNextMode && _delayNextMode < 0) {
		_makedNextMode = true;
		_game.PlayStage2Clear();
	}
}