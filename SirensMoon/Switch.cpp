#include "Switch.h"
#include "ModeGame.h"
#include "LinkLight.h"

Switch::Switch(Game& game, ModeGame& mode, ObjectDataStructs::SwitchData data)
	:Gimmick(game, mode, data.ID), _linkGimmiks{ data.links }, _accessible1{0}, _accessible2{ 0 },_cg3{-1}
{
	_pos = data.pos;
	_size = { 60,60 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	Vector2 fix = { 10,10 };
	_accessArea.min = _collision.min - fix;
	_accessArea.max = _collision.max + fix;
	_cg2 = ImageServer::LoadGraph("resource/Gimmick/switch.png");
	_cg3 = ImageServer::LoadGraph("resource/Gimmick/switch2.png");
	_cg = _cg3;

	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).RecieveCall(_linkGimmiks, false)) {
				_linkGimmickPositions.emplace_back(actor->GetPosition());
			}
		}
	}
}

void Switch::Update() {

	if (_game.GetFrameCount() % 180 == 0) {
		for (auto&& linkpos : _linkGimmickPositions) {
			_mode.GetActorServer().Add(std::make_unique<LinkLight>(_game, _mode, *this, linkpos));
		}
	}

	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
				_accessible1 = true;
			}
			else {
				_accessible1 = false;
			}
		}
		if (actor->GetType() == Type::PlayerB) {
			if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
				_accessible2 = true;
			}
			else {
				_accessible2 = false;
			}
		}
	}
	if (_accessible1) {
		if (_game.GetInputManager()->CheckInput("ACCESS", 'h', 0)) {
			LinkGimmickActivate(true);
			_cg = _cg2;
			return;
		}
	}
	if (_accessible2) {
		if (_game.GetInputManager()->CheckInput("ACCESS", 'h', 1)) {
			LinkGimmickActivate(true);
			_cg = _cg2;
			return;
		}
	}
	LinkGimmickActivate(false);
	_cg = _cg3;
	return;
}

void Switch::LinkGimmickActivate(bool flag) {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			dynamic_cast<Gimmick&>(*actor).RecieveCall(_linkGimmiks, flag);

		}
	}
}

void Switch::Debug(Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(window_pos, camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);
}