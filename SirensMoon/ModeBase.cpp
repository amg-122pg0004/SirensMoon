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

// çXêV
void ModeBase::Update() {
}

// ï`âÊ
void ModeBase::Render() {
}

void ModeBase::Debug() {

}

