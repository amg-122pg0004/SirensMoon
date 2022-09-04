#include "Switch.h"
#include "ModeGame.h"
#include "LinkLight.h"
#include "SquareLight.h"

Switch::Switch(Game& game, ModeGame& mode, ObjectDataStructs::SwitchData data)
	:Gimmick(game, mode, data.ID), _linkGimmiks{ data.links }, _accessible1{0}, _accessible2{ 0 },_cg3{-1}
{
	_activate = false;
	_pos = data.pos;
	_size = { 60,60 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	Vector2 fix = { 10,10 };
	_accessArea.min = _collision.min - fix;
	_accessArea.max = _collision.max + fix;
	if (data.RedFlag) {
		_cg3 = ImageServer::LoadGraph("resource/Gimmick/switch_r.png");
		_cg2 = ImageServer::LoadGraph("resource/Gimmick/switch2_r.png");
	}
	else {
		_cg3 = ImageServer::LoadGraph("resource/Gimmick/switch_b.png");
		_cg2 = ImageServer::LoadGraph("resource/Gimmick/switch2_b.png");
	}

	_cg = _cg3;
	SquareLight::SquareLightStats lightdata{"NULL","resource/Light/Light_3.png",false,{_pos.x - 75,_pos.y - 100},{200,200},200,150,100,255};
	_mode.GetActorServer().Add(std::make_unique<SquareLight>(_game,_mode,*this,lightdata));

	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).RecieveCall(_linkGimmiks, false)) {
				_linkGimmickPositions.emplace_back(actor->GetPosition());
			}
		}
	}
}

void Switch::Update() {

	if (_game.GetFrameCount() % 10 == 0) {
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
		if (_game.GetInputManager()->CheckInput("ACCESS", 't', 0)) {
			PlaySoundMem(SoundServer::Find("AccessSwitch"), DX_PLAYTYPE_BACK);
		}
		if (_game.GetInputManager()->CheckInput("ACCESS", 'h', 0)) {
			LinkGimmickActivate(true);
			_activate = true;
			_cg = _cg2;
			return;
		}
	}
	if (_accessible2) {
		if (_game.GetInputManager()->CheckInput("ACCESS", 't', 1)) {
			PlaySoundMem(SoundServer::Find("AccessSwitch"), DX_PLAYTYPE_BACK);
		}
		if (_game.GetInputManager()->CheckInput("ACCESS", 'h', 1)) {
			LinkGimmickActivate(true);
			_activate = true;
			_cg = _cg2;
			return;
		}
	}
	LinkGimmickActivate(false);
	if (_activate) {
		PlaySoundMem(SoundServer::Find("AccessSwitchEnd"), DX_PLAYTYPE_BACK);
	}
	_activate = false;
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