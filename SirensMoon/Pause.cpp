/*****************************************************************//**
 * \file   Pause.cpp
 * \brief  ポーズ画面です。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "Pause.h"
#include "ModeGame.h"


Pause::Pause(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size },_delay{30}
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/Pause/left.png");
	_cg2 = ImageServer::LoadGraph("resource/UI/Pause/right.png");
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
	if (_visible){
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
}

void Pause::Render() {
	if (_visible) {
		DrawGraph(0, 0, _cg, 1);
		DrawGraph(screen_W-splitscreen_W,0,_cg2, 1);
	}

}
