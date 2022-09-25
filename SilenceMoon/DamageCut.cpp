#include "DamageCut.h"
#include "Game.h"
#include "ModeGame.h"

class SplitWindow;

DamageCut::DamageCut(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase(game, mode, window, pos, size), _lifetime{ 60 }, _startTime{ 0 },_cgChange{false}
{
	_cg = ImageServer::LoadGraph("resource/Damage/damage.png");
	_cg2 = ImageServer::LoadGraph("resource/Damage/damage2.png");
	_easing = Easing::GetMode("OutQuint");
}

void DamageCut::Update() {

	auto elapsed = _game.GetFrameCount() - _startTime; // 経過時間
	auto start = 0;    // 開始値
	auto stop = 100;        // 終了値
	auto lifetime = 60 * 1; // 生存時間

	if (elapsed < lifetime) {
		// ラムダ式のイージング関数を使う
		_moveX = _easing(elapsed, start, stop, lifetime);
	}

	if (_visible) {
		--_lifetime;
	}
	if (_lifetime <= 0) {
		_visible = false;

		dynamic_cast<ModeGame&>(_mode).SetPauseGame(false);
	}
}

void DamageCut::Render() {
	if (_visible && _lifetime < 59) {
		DrawBox(0, 0, screen_W, static_cast<int>(_pos.y), GetColor(120, 20, 30), 1);
		DrawBox(0, static_cast<int>(_pos.y + _size.y), screen_W, screen_H, GetColor(120, 20, 30), 1);
		if (_cgChange) {
			DrawExtendGraph(static_cast<int>(_pos.x - _moveX),
				static_cast<int>(_pos.y),
				static_cast<int>(_pos.x + _size.x - _moveX),
				static_cast<int>(_pos.y + _size.y), _cg, 0);
		}
		else {
			DrawGraph(static_cast<int>(_pos.x - _moveX), static_cast<int>(_pos.y), _cg2, 0);
		}
	}
}

void DamageCut::DamageEvent() {
	_visible = true;
	_lifetime = 60;

	_startTime = _game.GetFrameCount();
	_cgChange = !_cgChange;
}
