#include "StickeyBomb.h"
#include "ModeGame.h"
#include "Explode.h"
#include "Game.h"
#include <string>
#include <sstream>
#include "ObjectiveUI.h"

StickyBomb::StickyBomb(Game& game, ModeGame& mode, ObjectDataStructs::StickyBombData data)
	:Gimmick(game,mode,data.ID),_accessible1{false},_accessible2{false},_player{nullptr}
{
	_renderPriority = 5000;
	_activate=false;
	_pos = data.pos;
	_size = { 30,30 };
	_collision.min = { 0,0 };
	_collision.max = { 0,0 };
	Vector2 range = { static_cast<double>(data.range), static_cast<double>(data.range)};
	_detectionArea.min = _pos + _size / 2 - range;
	_detectionArea.max = _pos + _size / 2 + range;
	_timer = data.timer;

	_accessArea.min = { 0,0 };
	_accessArea.max = { 0,0 };
	_cg = ImageServer::LoadGraph("resource/Gimmick/Sticky/down.png");
}

void StickyBomb::Update() {
	if (!_activate) {
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
				if (Intersect(_detectionArea, actor->GetCollision())) {
					_activate = true;
					PlaySoundMem(SoundServer::Find("MicroBomAlarm"), DX_PLAYTYPE_LOOP);
					_player = actor.get();
					if (actor->GetType() == Type::PlayerA) {
						dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()->ChangeWarning(0);
						dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()->ChangeWarning(1);
					}
					if (actor->GetType() == Type::PlayerB) {
						dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()->ChangeWarning(1);
						dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()->ChangeWarning(0);
					}
				}

			}
		}
	}
	else {
		--_timer;
		if (_timer <= 0) {
			_mode.GetActorServer().Add(std::make_unique<Explode>(_game, _mode, _pos));
			StopSoundMem(SoundServer::Find("MicroBomAlarm"));
			PlaySoundMem(SoundServer::Find("ActiveTrapBom"), DX_PLAYTYPE_BACK);
			dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
				->ChangeMessage("重要宇宙人特定し、捕獲せよ", 2);
			dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()
				->ChangeMessage("重要宇宙人特定し、捕獲せよ", 2);
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
						_accessible2 = true;
						if (_game.GetInputManager()->CheckInput("ACCESS", 't', 1)) {
							StopSoundMem(SoundServer::Find("MicroBomAlarm"));
							PlaySoundMem(SoundServer::Find("MicroBomRelease"), DX_PLAYTYPE_LOOP);
							dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
								->ChangeMessage("重要宇宙人特定し、捕獲せよ", 2);
							dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()
								->ChangeMessage("重要宇宙人特定し、捕獲せよ", 2);
							_dead = true;
						}
					}
					else {
						_accessible2=false;
					}
				}
			}
		}
		else if (_player->GetType() == Type::PlayerB) {
			for (auto&& actor : _mode.GetObjects()) {
				if (actor->GetType() == Type::PlayerA) {
					if (Intersect(_accessArea, actor->GetCollision())) {
						_accessible1 = true;
						if (_game.GetInputManager()->CheckInput("ACCESS", 't', 0)) {
							StopSoundMem(SoundServer::Find("MicroBomAlarm"));
							PlaySoundMem(SoundServer::Find("MicroBomRelease"), DX_PLAYTYPE_LOOP);
							dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
								->ChangeMessage("重要宇宙人特定し、捕獲せよ", 2);
							dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()
								->ChangeMessage("重要宇宙人特定し、捕獲せよ", 2);
							_dead = true;
						}
					}
					else {
						_accessible1 = false;
					}
				}
			}
		}
	}
}

void StickyBomb::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x-_size.x/2)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y - _size.y / 2)
		, _cg
		, 1);
	if (_activate) {
		std::stringstream ss;
		ss << "爆発まで" << _timer / 60 << "\n";
		DrawString(static_cast<int>(_pos.x + window_pos.x - camera_pos.x - _size.x / 2),
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y - _size.y / 2) - 60,
			ss.str().c_str(),
			GetColor(255, 255, 255));
	}
}

void StickyBomb::Debug(Vector2 window_pos, Vector2 camera_pos){
	if (!_activate) {
		_detectionArea.Draw2(window_pos, camera_pos);
	}
	else {
		_accessArea.Draw2(window_pos, camera_pos);
	}

}