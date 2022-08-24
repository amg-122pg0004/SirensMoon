/*****************************************************************//**
 * \file   HPItem.h
 * \brief  HP�񕜃A�C�e��
 * 
 * \author �y�������Y
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
	Type GetType() { return Type::Item; }
	//void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
private:

};