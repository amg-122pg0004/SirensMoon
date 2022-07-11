/*
** ModeBase
*/

#include "ModeBase.h"

class Game;

ModeBase::ModeBase(Game& game)
	: _game(game)
	, _actorServer(game)
	, _dead(false)
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

