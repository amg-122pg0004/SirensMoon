#pragma once
#include <vector>
#include "Actor.h"

class Game;
class ModeGame;

class Gimmick: public Actor{
public:
	enum class GimmickType {
		BarrierA,
		BarrierB,
		FloorLamp,
		Switch,
		SwitchArea,
		Teleporter,
		Door,
		Mine,
		TNT,
		StickyBomb,
		BreakableObject,
		DegitalLetter,
		BigServer,
		BigGenerator,
		BigGun,
		ScreenPump,
		MiniShuttle
	};
	virtual GimmickType GetGimmickType() = 0;

	Gimmick(Game& game, ModeGame& mode,int ID);

	virtual bool RecieveCall(std::vector<int> IDs,bool flag);
	void  SetActivate() { _activate = true; }
	bool GetActivate() { return _activate; }
	int GetID() { return _id; }

protected:
	/*�N�����Ă��邩*/
	bool _activate;

	/*Tiled��Ŋ���U����ID���擾*/
	int _id;
};