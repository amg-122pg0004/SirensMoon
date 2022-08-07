#include "Switch.h"
#include "ModeGame.h"
#include "ImageServer.h"

Switch::Switch(Game& game, ModeGame& mode, MapChips::SwitchData data)
	:Gimmick(game, mode, data.ID), _linkGimmiks{ data.links }
{
	_pos = data.pos;
	_size = { 60,60 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	Vector2 fix = { 10,10 };
	_accessArea.min = _collision.min - fix;
	_accessArea.max = _collision.max + fix;
	_cg = ImageServer::LoadGraph("resource/Gimmick/switch.png");
}

void Switch::Update() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			if (_game.GetInputManager()->CheckInput("ACCESS", 'h', 0)) {
				if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
					LinkGimmickActivate(true);
					return;
				}
			}
			if (_game.GetInputManager()->CheckInput("ACCESS", 'r', 0)) {
				if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
					LinkGimmickActivate(false);
					return;
				}
			}
		}
		if (actor->GetType() == Type::PlayerB) {
			if (_game.GetInputManager()->CheckInput("ACCESS", 'h', 1)) {
				if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
					LinkGimmickActivate(true);
					return;
				}
			}
			if (_game.GetInputManager()->CheckInput("ACCESS", 'r', 1)) {
				if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
					LinkGimmickActivate(false);
					return;
				}
			}
		}
	}
	LinkGimmickActivate(false);
	return;
}

void Switch::LinkGimmickActivate(bool flag) {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			dynamic_cast<Gimmick&>(*actor).RecieveCall(_linkGimmiks, flag);
		}
	}
}

void Switch::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(stageNum, window_pos, camera_pos);
	_accessArea.Draw2(stageNum, window_pos, camera_pos);
}
