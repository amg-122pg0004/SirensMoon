#include "AimUI.h"
#include "Game.h"
#include "ModeGame.h"
#include "Boss.h"
#include "Screen_Fade.h"

class SplitWindow;

AimUI::AimUI(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase(game, mode, window, pos, size), _gameClearTimer{ 120 }, _gameClear{ false }
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/AimUI/frame.png");
	_cg_cursor = ImageServer::LoadGraph("resource/UI/AimUI/cursor.png");
	_cg_Info = ImageServer::LoadGraph("resource/UI/Info/RailGunInfo.png");
	_pos_cursor = { 930 / 2,1080 / 2 };
	_visible = true;
}

void AimUI::Update() {
	if (_gameClear) {
		--_gameClearTimer;
		if (_gameClearTimer < 0) {
			_game.NextMode();
		}
		return;
	}
	else {
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Actor::Type::Boss) {
				auto box = dynamic_cast<Boss&>(*actor).GetHitBox();
				auto pos = (box.min + box.max) / 2;
				_pos_cursor = pos;
			}
		}
		if (_pos_cursor.x < 0) {
			_pos_cursor.x = 0;
		}
		if (_pos_cursor.x > splitscreen_W) {
			_pos_cursor.x = splitscreen_W;
		}
		if (_pos_cursor.y < 0) {
			_pos_cursor.y = 0;
		}
		if (_pos_cursor.y > screen_H) {
			_pos_cursor.y = screen_H;
		}
		if (_window.GetWindowNo() != 0) {
			return;
		}
		if (_inputManager->CheckInput("ACTION", 't', 0)) {
			if (CheckSoundMem(SoundServer::Find("BigRailgunShoot")) == 0) {
				PlaySoundMem(SoundServer::Find("BigRailgunShoot"), DX_PLAYTYPE_BACK);
			}
			if (CheckSoundMem(SoundServer::Find("BigRailgunHit")) == 0) {
				PlaySoundMem(SoundServer::Find("BigRailgunHit"), DX_PLAYTYPE_BACK);
			}
			_gameClear = true;
			for (auto&& window : static_cast<ModeGame&>(_mode).GetSplitWindow()) {
				auto fade = std::make_unique<Screen_Fade>(_game, _mode, *window, window->GetWindowPos(), _size);
				fade->SetEffect(0, 120, GetColor(255, 255, 255), false, false);
				window->GetUIServer2().Add(std::move(fade));
			}
			for (auto&& actor : _mode.GetObjects()) {
				if (actor->GetType() == Actor::Type::Boss) {
					dynamic_cast<Boss&>(*actor).Dead();
				}
			}
		}
	}

}

void AimUI::Render() {
	SetDrawArea(static_cast<int>(_pos.x), static_cast<int>(_pos.y), static_cast<int>(_pos.x + splitscreen_W), static_cast<int>(_pos.y + screen_H));
	if (_visible) {
		DrawRotaGraph(static_cast<int>(_pos.x+_pos_cursor.x), static_cast<int>(_pos.y+_pos_cursor.y), 1.0, 0.0, _cg_cursor, 1);
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 1);
		if (_window.GetWindowNo() != 0) {
			return;
		}
		DrawRotaGraph(static_cast<int>(_pos.x + splitscreen_W / 2)
			, static_cast<int>(_pos.y + screen_H / 2)
			, 1.0, 0.0
			, _cg_Info, 1);
	}

	SetDrawArea(0, 0, screen_W, screen_H);
}
