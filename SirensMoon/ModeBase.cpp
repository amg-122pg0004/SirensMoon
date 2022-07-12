/*
** ModeBase
*/

#include "ModeBase.h"
class Game;

ModeBase::ModeBase(Game& game)
	: _game(game)

	, _dead(false)
{
	_actorServer = std::make_unique<ActorServer>(_game);
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

