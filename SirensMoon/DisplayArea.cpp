#include "DisplayArea.h"

DisplayArea::DisplayArea(Game& game, ModeGame& mode,Actor& owner)
	:Actor(game,mode),_owner{owner}
{

}
