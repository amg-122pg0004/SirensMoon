#include "HPItem.h"
#include "ImageServer.h"
#include "ModeGame.h"
/*****************************************************************//**
 * \file   HPItem.cpp
 * \brief  HP回復アイテム
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/
#include "Player.h"

HPItem::HPItem(Game& game, ModeBase& mode,Vector2 pos)
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
		if (actor->GetType() == Type::Player) {
			if (Intersect(_collision, actor->GetCollision())) {
				dynamic_cast<Player&>(*actor).Heal();
				_dead = true;
			}
		}
	}
}
