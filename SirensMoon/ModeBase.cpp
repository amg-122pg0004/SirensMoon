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

// çXêV
void ModeBase::Update() {
}

// ï`âÊ
void ModeBase::Render() {
}

