#include "HPItem.h"
#include "ImageServer.h"
#include "ModeGame.h"
/*****************************************************************//**
 * \file   HPItem.cpp
 * \brief  HPñACe
 *
 * \author y«¾Y
 * \date   July 2022
 *********************************************************************/
#include "Player.h"

HPItem::HPItem(Game& game, ModeGame& mode,Vector2 pos)
	:Actor(game, mode)
{
	_cg = ImageServer::LoadGraph("resource/Item/HP.png");
	_pos = pos;
	_size = { 40,40 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
}

void HPItem::Update(){
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::PlayerA|| actor->GetType() == Type::PlayerB) {
			if (Intersect(_collision, actor->GetCollision())) {
				if (dynamic_cast<Player&>(*actor).GetHP() < 3) {
					dynamic_cast<Player&>(*actor).Heal();
					_dead = true;
				}
			}
		}
	}
}
