#include "HPItem.h"
#include "ModeGame.h"
/*****************************************************************//**
 * \file   HPItem.cpp
 * \brief  HP回復アイテム
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/
#include "Player.h"

HPItem::HPItem(Game& game, ModeGame& mode,Vector2 pos)
	:Actor(game, mode),_fall{true}, _fallTimer{300}
{
	_cg = ImageServer::LoadGraph("resource/Item/HP.png");
	_pos = pos;
	_size = { 60,60 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	_renderPriority = -1;
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
	if (!_fall) {
		return;
	}
	--_fallTimer;
	if (_fallTimer < 0) {
		_dead = true;
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

void HPItem::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 1);
}

void HPItem::UpdateCollision() {
	_collision.min = _pos;
	_collision.max = _pos + _size;
}