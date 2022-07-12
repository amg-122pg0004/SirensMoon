/*
** ModeBase
*/

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

// �X�V
void ModeBase::Update() {
}

// �`��
void ModeBase::Render() {
}

void ModeBase::Debug() {

}

