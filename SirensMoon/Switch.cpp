#include "Switch.h"
#include "ModeGame.h"
#include "LinkLight.h"
#include "SquareLight.h"

Switch::Switch(Game& game, ModeGame& mode, SwitchData data)
	:Gimmick(game, mode, data.ID), _linkGimmiks{ data.links }
	, _accessible1{ 0 }, _accessible2{ 0 }, _cg3{ -1 }, _timer{ 120 }
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
	SquareLightStats lightdata;
	_mode.GetActorServer().Add(std::make_unique<SquareLight>(_game, _mode, *this, lightdata));

	/*連携しているギミックの位置を取得*/
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).RecieveCall(_linkGimmiks, false)) {
				_linkGimmickPositions.emplace_back(actor->GetPosition());
			}
		}
	}
}

void Switch::Update() {
	if (_linkGimmiks.empty()) {
		return;
	}

	/*スイッチから連携ギミックへエフェクト発生*/
	if (_game.GetFrameCount() % 10 == 0) {
		for (auto&& linkpos : _linkGimmickPositions) {
			_mode.GetActorServer().Add(std::make_unique<LinkLight>(_game, _mode, *this, linkpos));
		}
	}

	if (_firstActivate!=0) {
		--_timer;
		if (_timer < 60&& _timer >= 40) {
			LinkGimmickActivate(true);
			_activate = true;
			_cg = _cg2;
			return;
		}
		if (_timer == 0) {
			_mode.GetSplitWindow()[_firstActivate - 1]->GetCamera()->SetMovable(true);
			_mode.GetSplitWindow()[_firstActivate-1]->GetCamera()->SetPosition(_pos+_size/2);
			return;
		}
	}

	/*プレイヤーがアクション可能位置にいるか確認*/
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
			if (_firstActivate==0) {
				FirstActivateEvent(1);
			}
			else if (_timer < 60) {
				LinkGimmickActivate(true);
			}
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
			if (_firstActivate==0) {
				FirstActivateEvent(2);
			}
			else if (_timer < 60) {
				LinkGimmickActivate(true);
			}
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

void Switch::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(window_pos, camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);
}

void Switch::FirstActivateEvent(int eventPlayer) {
	_firstActivate = eventPlayer;

	_roomPosition = CheckRoomPosition();
	double x = floor(_linkGimmickPositions[0].x / (static_cast<double>(splitscreen_W)));
	double y = floor(_linkGimmickPositions[0].y / (static_cast<double>(screen_H)));
	Vector2 linkRoom = { x,y };
	if (_roomPosition == linkRoom) {
		_timer = 0;
	}
	else {
		_mode.GetSplitWindow()[_firstActivate - 1]->GetCamera()->SetPosition(_linkGimmickPositions[0]);
		_mode.GetSplitWindow()[_firstActivate - 1]->GetCamera()->SetMovable(false);
	}
}