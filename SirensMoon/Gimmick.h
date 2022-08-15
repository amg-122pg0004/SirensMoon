#pragma once
#include <vector>
#include "Actor.h"

class Game;
class ModeGame;

class Gimmick: public Actor{
public:
	enum class GimmickType {
		FloorLamp,
		Switch,
		Teleporter,
		Door,
		Mine,
		TNT,
		StickyBomb
	};
	virtual GimmickType GetGimmickType() = 0;

	Gimmick(Game& game, ModeGame& mode,int ID);

	bool RecieveCall(std::vector<int> IDs,bool flag);

	bool GetActivate() { return _activate; }
	int GetID() { return _id; }



protected:
	/*�N�����Ă��邩*/
	bool _activate;

	/*Tiled��Ŋ���U����ID���擾*/
	int _id;

};
