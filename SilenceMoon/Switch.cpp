#include "Switch.h"
#include "ModeGame.h"
#include "LinkLight.h"
#include "SquareLight.h"
#include "Screen_Fade.h"

Switch::Switch(Game& game, ModeGame& mode, SwitchData data)
	:Gimmick(game, mode, data.ID), _linkGimmiks{ data.links },_stopRay{false}
	, _accessible1{ 0 }, _accessible2{ 0 }, _cg3{ -1 }
	, _timer{ 120 }, _projectionNumber{ data.projectionNumber },_firstActivate{-1}
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
				Vector2 pos=actor->GetPosition();
				Vector2 size = actor->GetSize();
				_linkGimmickPositions.emplace_back(pos+size/2);
			}
		}
	}
}

void Switch::Update() {

	/*スイッチから連携ギミックへエフェクト発生*/
	RayToLinks();


	if (_firstActivate != -1) {
		--_timer;
		if (_timer == 105) {
			auto&& window = _mode.GetSplitWindow()[_firstActivate];
			window->GetCamera()->SetPosition(_linkGimmickPositions[0]);
			window->GetCamera()->SetMovable(false);
		}
		if (_timer < 60 && _timer >= 40) {
			LinkGimmickActivate(true);
			_activate = true;
			_cg = _cg2;
			return;
		}
		if (_timer == 0) {
			_mode.GetSplitWindow()[_firstActivate]->GetCamera()->SetMovable(true);
			_mode.GetSplitWindow()[_firstActivate]->GetCamera()->SetPosition(_pos + _size / 2);
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
			_stopRay = true;
			if (_firstActivate == -1) {
				FirstActivateEvent(0);
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
			_stopRay = true;
			if (_firstActivate == -1) {
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
	if (LinkGimmickActivate(false)) {
		_stopRay = false;
	}
	if (_activate) {
		if (CheckSoundMem(SoundServer::Find("AccessSwitchEnd")) == 0) {
			PlaySoundMem(SoundServer::Find("AccessSwitchEnd"), DX_PLAYTYPE_BACK);
		}
	}
	_activate = false;
	_cg = _cg3;
	return;
}

bool Switch::LinkGimmickActivate(bool flag) {
	if (_linkGimmiks.empty()) {
		return false;
	}

	bool result{ false };
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).RecieveCall(_linkGimmiks, flag)) {
				result = true;
			}
		}
	}
	return result;
}

void Switch::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(window_pos, camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);
}

void Switch::FirstActivateEvent(int eventPlayer) {
	if (_linkGimmickPositions.empty()) {
		return;
	}

	_firstActivate = eventPlayer;

	_roomPosition = CheckRoomPosition();
	double x = floor(_linkGimmickPositions[0].x / (static_cast<double>(splitscreen_W)));
	double y = floor(_linkGimmickPositions[0].y / (static_cast<double>(screen_H)));
	Vector2 linkRoom = { x,y };
	if (_roomPosition == linkRoom) {
		_timer = 0;
	}
	else {
		auto&& window= _mode.GetSplitWindow()[_firstActivate];
		Vector2 size{ 0,0 };
		auto fade = std::make_unique<Screen_Fade>(_game,_mode,*window,window->GetWindowPos(),size);
		fade->SetEffect(1,15,GetColor(0,0,0),false, false);
		window->GetUIServer2().Add(std::move(fade));
		auto fade2 = std::make_unique<Screen_Fade>(_game, _mode, *window, window->GetWindowPos(), size);
		fade2->SetEffect(16, 15, GetColor(0, 0, 0), true, false);
		window->GetUIServer2().Add(std::move(fade2));

		auto fade3 = std::make_unique<Screen_Fade>(_game, _mode, *window, window->GetWindowPos(), size);
		fade3->SetEffect(105, 15, GetColor(0, 0, 0), false, false);
		window->GetUIServer2().Add(std::move(fade3));
		auto fade4 = std::make_unique<Screen_Fade>(_game, _mode, *window, window->GetWindowPos(), size);
		fade4->SetEffect(120, 15, GetColor(0, 0, 0), true, false);
		window->GetUIServer2().Add(std::move(fade4));
	}
}

void Switch::RayToLinks(){
	if (_linkGimmickPositions.empty()) {
		return;
	}
	if (_stopRay) {
		return;
	}
	if (_game.GetFrameCount() % 60 * 0.8 == 0) {
		int loop = Math::Min(_projectionNumber, static_cast<int>(_linkGimmickPositions.size()));
		for (int i = 0; i < loop; ++i) {
			_mode.GetActorServer().Add(std::make_unique<LinkLight>(_game, _mode, *this, _linkGimmickPositions[i]));
		}
	}
}
