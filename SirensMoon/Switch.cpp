#include "Switch.h"
#include "ModeGame.h"
#include "ImageServer.h"

Switch::Switch(Game& game, ModeGame& mode, MapChips::SwitchData data)
	:Gimmick(game, mode, data.ID), _linkGimmiks{ data.links }
{
	_pos = data.pos;
	_size = { 40,40 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	_cg = ImageServer::LoadGraph("resource/Gimmick/switch.png");
}

void Switch::Update() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			if (_game.GetInputManager()->CheckInput("ACTION", 't', 0)) {
				if (Intersect(_collision, dynamic_cast<Player&>(*actor).GetCollision())) {
					LinkGimmickActivate(true);
				}
			}
			if (_game.GetInputManager()->CheckInput("ACTION", 'r', 0)) {
				if (Intersect(_collision, dynamic_cast<Player&>(*actor).GetCollision())) {
					LinkGimmickActivate(false);
				}
			}
		}
		if (actor->GetType() == Type::PlayerB) {
			if (_game.GetInputManager()->CheckInput("ACTION", 't', 1)) {
				if (Intersect(_collision, dynamic_cast<Player&>(*actor).GetCollision())) {
					LinkGimmickActivate(true);
				}
			}
			if (_game.GetInputManager()->CheckInput("ACTION", 'r', 1)) {
				if (Intersect(_collision, dynamic_cast<Player&>(*actor).GetCollision())) {
					LinkGimmickActivate(false);
				}
			}
		}
	}
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
}
