/*****************************************************************//**
 * \file   BulletItem.cpp
 * \brief  ’e–ò‰ñ•œƒAƒCƒeƒ€
 * 
 * \author “y‹«‘¾˜Y
 * \date   July 2022
 *********************************************************************/

#include "BulletItem.h"
#include "ModeGame.h"
#include "Player.h"

BulletItem::BulletItem(Game& game, ModeGame& mode,Vector2 pos)
	:Actor(game,mode)
{
	_cg = ImageServer::LoadGraph("resource/Item/Ammo.png");
	_pos = pos;
	_size = { 40,40 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	_renderPriority = -1;
}

void BulletItem::Update() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::PlayerA|| actor->GetType() == Type::PlayerB) {
			if(Intersect(_collision, actor->GetCollision())) {
				dynamic_cast<Player&>(*actor).TakeAmmo();
				_dead = true;
			}
		}
	}
}

void BulletItem::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 1);
}