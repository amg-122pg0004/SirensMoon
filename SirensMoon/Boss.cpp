#include "Boss.h"

Boss::Boss(Game& game, ModeGame& mode,Player& p1,Player& p2) 
	:Actor(game,mode),_player1{p1},_player2{p2}
{
	std::vector<int> handle;
	handle.resize(1);
	ImageServer::LoadDivGraph("resource/Boss/wait.png",1,1,1,420,840,handle.data());
	_cg[State::Wait] = handle;
}
