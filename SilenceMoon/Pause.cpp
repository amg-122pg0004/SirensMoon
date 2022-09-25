/*****************************************************************//**
 * \file   Pause.cpp
 * \brief  ポーズ画面です。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "Pause.h"
#include "ModeGame.h"
class SplitWindow;

Pause::Pause(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size },_delay{30}
{
	_inputManager = _game.GetInputManager();
	if (window.GetWindowNo() == 0) {
		_cg = ImageServer::LoadGraph("resource/UI/Pause/left.png");
	}
	else {
		_cg = ImageServer::LoadGraph("resource/UI/Pause/right.png");
	}

	_UIPriority = 10;
}

void Pause::Update() {
	--_delay;
	if (_delay > 0) {
		return;
	}
	if (_inputManager->CheckInput("PAUSE", 't', 0) ||
		_inputManager->CheckInput("PAUSE", 't', 1)) {
		_visible = !_visible;
		if (_visible) {
			dynamic_cast<ModeGame&>(_mode).SetPauseGame(true);
		}
		else {
			dynamic_cast<ModeGame&>(_mode).SetPauseGame(false);
		}
	}
#ifdef _DEBUG
	if (_visible && _window.GetWindowNo() == 0) {
		if (_inputManager->CheckInput("BULLET1", 't', 0) ||
			_inputManager->CheckInput("BULLET1", 't', 1)) {
			_mode.CallPlayStage1();
		}
		if (_inputManager->CheckInput("BULLET2", 't', 0) ||
			_inputManager->CheckInput("BULLET2", 't', 1)) {
			_mode.CallPlayStage2();
		}
		if (_inputManager->CheckInput("DEBUG", 't', 0) ||
			_inputManager->CheckInput("DEBUG", 't', 1)) {
			_mode.CallPlayStage3();
		}
	}
#endif // _DEBUG
}

void Pause::Render() {
	if (_visible) {
		SetDrawArea(0,0,screen_W,screen_W);
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 1);
	}

}
