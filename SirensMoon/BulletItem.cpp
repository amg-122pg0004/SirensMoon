/*****************************************************************//**
 * \file   BulletItem.cpp
 * \brief  ’e–ò‰ñ•œƒAƒCƒeƒ€
 *
 * \author “y‹«‘¾˜Y
 * \date   July 2022
 *********************************************************************/

#include "BulletItem.h"
#include "ModeGame.h"
#include "PlayerA.h"

BulletItem::BulletItem(Game& game, ModeGame& mode, Vector2 pos)
	:Actor(game, mode), _fall{ true }
{
	_cg = ImageServer::LoadGraph("resource/Item/ammo.png");
	_pos = pos;
	_size = { 60,60 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	_renderPriority = -1;
}

void BulletItem::Update() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			if (Intersect(_collision, actor->GetCollision())) {
				if (dynamic_cast<PlayerA&>(*actor).GetAmmo() < 5) {
					dynamic_cast<PlayerA&>(*actor).TakeAmmo();
					PlaySoundMem(SoundServer::Find("TakeAmmo"), DX_PLAYTYPE_BACK);
					_dead = true;
				}
			}
		}
	}
	if (!_fall) {
		return;
	}
	AABB col{ _collision };
	col.max = { _collision.max.x,_collision.max.y - 40 };
	if (!_mode.GetMapChips()->IsHit(col, true)) {
		_fall = false;
	}
	else {
		_pos.y += 5;
		UpdateCollision();
	}
}

void BulletItem::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 1);
}
void BulletItem::UpdateCollision() {
	_collision.min = _pos;
	_collision.max = _pos + _size;
}
