/*****************************************************************//**
 * \file   Gimmick.h
 * \brief  ギミックの親クラス
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
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
	/*起動しているか*/
	bool _activate;

	/*Tiled上で割り振られるIDを取得*/
	int _id;
};