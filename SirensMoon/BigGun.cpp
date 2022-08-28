#include "BigGun.h"
#include "ModeGame.h"

BigGun::BigGun(Game& game, ModeGame& mode, ObjectDataStructs::BigGunData data)
	:Gimmick(game,mode,data.ID),_accessible{false}
{

}