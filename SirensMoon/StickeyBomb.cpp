#include "StickeyBomb.h"
#include "ModeGame.h"
#include "Explode.h"
#include "Game.h"

StickyBomb::StickyBomb(Game& game, ModeGame& mode, ObjectDataStructs::StickyBombData data)
	:Gimmick(game,mode,data.ID)
{
	_activate=false;
	_pos = data.pos;
	_size = { 30,30 };
	_collision.min = { 0,0 };
	_collision.max = { 0,0 };
	Vector2 range = { static_cast<double>(data.range), static_cast<double>(data.range)};
	_detectionArea.min = _pos + _size / 2 - range;
	_detectionArea.max = _pos + _size / 2 + range;
	_timer = data.timer;

	_cg = ImageServer::LoadGraph("resource/Gimmick/sticky.png");
}

void StickyBomb::Update() {
	if (!_activate) {
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
				if (Intersect(_detectionArea, actor->GetCollision())) {
					_activate = true;
					_player = actor.get();
				}
			}
		}
	}
	else {
		--_timer;
		if (_timer <= 0) {
			_mode.GetActorServer().Add(std::make_unique<Explode>(_game, _mode, _pos));
			_dead = true;
		}

		auto col_pos=_player->GetCollision();
		_pos = (col_pos.min + col_pos.max) / 2;
		_accessArea.min={_pos.x-_size.x*1.2,_pos.y - _size.y * 1.2 };
		_accessArea.max = { _pos.x + _size.x * 1.2,_pos.y + _size.y * 1.2};

		if (_player->GetType() == Type::PlayerA) {
			for (auto&& actor : _mode.GetObjects()) {
				if (actor->GetType() == Type::PlayerB) {
					if (Intersect(_accessArea, actor->GetCollision())) {
						if (_game.GetInputManager()->CheckInput("ACCESS", 't', 1)) {
							_dead = true;
						}
					}
				}
			}
		}
		else if (_player->GetType() == Type::PlayerB) {
			for (auto&& actor : _mode.GetObjects()) {
				if (actor->GetType() == Type::PlayerA) {
					if (Intersect(_accessArea, actor->GetCollision())) {
						if (_game.GetInputManager()->CheckInput("ACCESS", 't', 0)) {
							_dead = true;
						}
					}
				}
			}
		}
	}
}

void StickyBomb::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x-_size.x/2)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y - _size.y / 2)
		, _cg
		, 0);
}

void StickyBomb::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	if (!_activate) {
		_detectionArea.Draw2(stageNum, window_pos, camera_pos);
	}
	else {
		_accessArea.Draw2(stageNum, window_pos, camera_pos);
	}

}
