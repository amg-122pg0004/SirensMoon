/*****************************************************************//**
 * \file   BulletItem.h
 * \brief  弾薬回復アイテム
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/
#pragma once
#include "Actor.h"
#include "Math.h"

class Game;
class ModeGame;

class BulletItem :public Actor {
public:
	BulletItem(Game& game, ModeGame& mode, Vector2 pos);
	Type GetType() { return Type::Item; }
	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
private:
	void UpdateCollision();
	bool _fall;
};


