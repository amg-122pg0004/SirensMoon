/*****************************************************************//**
 * \file   Pause.cpp
 * \brief  ポーズ画面を表示するUIです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "Pause.h"
#include "ModeGame.h"


Pause::Pause(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/Pause/left.png");
	_cg2 = ImageServer::LoadGraph("resource/UI/Pause/right.png");
	
}

void Pause::Update() {
	/*
	if (_inputManager->CheckInput("PAUSE", 'h', 0) ||
		_inputManager->CheckInput("PAUSE", 'h', 1)) {
		dynamic_cast<ModeGame&>(_mode).SetPauseGame(1);
		_visible = true;
	}
	*/
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

}

void Pause::Render() {
	if (_visible) {
		DrawGraph(0, 0, _cg, 1);
		DrawGraph(screen_W-splitscreen_W,0,_cg2, 1);
	}

}
