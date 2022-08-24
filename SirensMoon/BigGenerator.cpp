#include "BigGenerator.h"

BigGenerator::BigGenerator(Game& game, ModeGame& mode, int ID, std::vector<bool> signal)
	:Gimmick(game,mode,ID),_signal{signal}
{

}
