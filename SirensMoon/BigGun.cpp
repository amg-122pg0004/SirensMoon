#include "BigGun.h"
#include "ModeGame.h"

BigGun::BigGun(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data, std::vector<bool> signal)
	:Gimmick(game,mode,data.ID),_accessible{false}
{

}