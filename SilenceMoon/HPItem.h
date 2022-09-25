/*****************************************************************//**
 * \file   HPItem.h
 * \brief  HP回復アイテム
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/
#pragma once
#include "Actor.h"
#include "Math.h"

class Game;
class ModeGame;


class HPItem :public Actor {
public:
	HPItem(Game& game, ModeGame& mode,Vector2 pos);
	void Update()override;
	Type GetType() { return Type::HPItem; }
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
private:
	void UpdateCollision();
	bool _fall;
	int _fallTimer;
};