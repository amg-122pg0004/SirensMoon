#include "Gimmick.h"

Gimmick::Gimmick(Game& game,ModeGame& mode,int ID)
	:Actor(game,mode),_activate{true},_id{ID}
{

}

bool Gimmick::RecieveCall(std::vector<int> IDs, bool flag) {
	for (int id : IDs) {
		if (id == _id) {
			_activate = flag;
			return true;
		}
	}
	return false;
}
