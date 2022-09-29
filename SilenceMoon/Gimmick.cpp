/*****************************************************************//**
 * \file   Gimmick.cpp
 * \brief  ギミックの親クラス
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "Gimmick.h"

Gimmick::Gimmick(Game& game,ModeGame& mode,int ID)
	:Actor(game,mode),_activate{true},_id{ID}
{
	_renderPriority = -1;
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
