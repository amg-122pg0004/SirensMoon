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
		StickyBomb,
		BreakableObject,
		DegitalLetter,
		BigServer,
		BigGenerator,
		BigGun
	};
	virtual GimmickType GetGimmickType() = 0;

	Gimmick(Game& game, ModeGame& mode,int ID);

	bool RecieveCall(std::vector<int> IDs,bool flag);
	void  SetActivate() { _activate = true; }
	bool GetActivate() { return _activate; }
	int GetID() { return _id; }



protected:
	/*起動しているか*/
	bool _activate;

	/*Tiled上で割り振られるIDを取得*/
	int _id;

};