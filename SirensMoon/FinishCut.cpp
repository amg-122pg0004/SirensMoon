#include "FinishCut.h"
#include "Game.h"
#include "ModeGame.h"

FinishCut::FinishCut(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase(game, mode, pos, size), _lifetime{ 240 }, _startTime{ 0 },_elapsed{0},_visible2{0}
{
	_cg = ImageServer::LoadGraph("resource/Damage/Special/special.png");
	_cg_screen= ImageServer::LoadGraph("resource/UI/screen.png");
	std::string path{ "resource/Damage/Special/" };
	std::string ext{ ".png" };
	for (int i = 1; i <= 42; ++i) {
		_cgBlood.push_back(ImageServer::LoadGraph(path + std::to_string(i) + ext));
	}
	_easing = Easing::GetMode("InCubic");
	_startTime = _game.GetFrameCount();
	_UIPriority = 10;
}

void FinishCut::Update() {

	--_lifetime;
	auto elapsed = _game.GetFrameCount() - _startTime; // 経過時間
	auto start = 255;    // 開始値
	auto stop = 0;        // 終了値
	auto lifetime = 20 ; // 生存時間

	if (elapsed < lifetime+10) {
		// ラムダ式のイージング関数を使う
		_alpha = _easing(elapsed, start, stop, lifetime);
		if (_alpha < 255*0.2) {
			_visible2 = true;
		}
	}
	if (_lifetime <= 0) {
		_visible = false;
	}
	_elapsed = elapsed;
}

void FinishCut::Render(){
	if (_visible) {

		if (_visible2) {
			DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 0);
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			for (int i = 0; i < 42; ++i) {
				auto pos = _pos;
				double x = sin(Math::ToRadians(8.57142f * i));
				double y = cos(Math::ToRadians(8.57142f * i)) * -1;
				Vector2 dir = { x * (_elapsed - 100) * 0.18,y * (_elapsed - 100) * 0.18 };
				pos += dir;
				DrawGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), _cgBlood[i], 1);
			}
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}

		DrawBox(0, 0, screen_W, static_cast<int>(_pos.y), GetColor(0, 0, 0), 1);
		DrawBox(0, static_cast<int>(_pos.y + _size.y), screen_W, screen_H, GetColor(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,_alpha);
		DrawBox(0, 0, screen_W, screen_H, GetColor(255, 255, 255), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);

	}
}

void FinishCut::TargetKillEvent() {
	_visible = true;
	_visible2 = false;
	_lifetime = 240;
	_startTime = _game.GetFrameCount();
}