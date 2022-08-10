/*****************************************************************//**
 * \file   Pause.cpp
 * \brief  ポーズ画面を表示するUIです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "Pause.h"
#include "ImageServer.h"
#include "ModeGame.h"


Pause::Pause(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/pause.png");
	
}

void Pause::Update() {
	if (_inputManager->CheckInput("PAUSE", 'h', 0) ||
		_inputManager->CheckInput("PAUSE", 'h', 1)) {
		dynamic_cast<ModeGame&>(_mode).SetPauseGame(1);
		_visible = true;
	}
	else if (_inputManager->CheckInput("PAUSE", 'r', 0) ||
		_inputManager->CheckInput("PAUSE", 'r', 1)) {
		dynamic_cast<ModeGame&>(_mode).SetPauseGame(0);
		_visible = false;
	}

}

void Pause::Render() {
	if (_visible) {
		int x, y;
		GetGraphSize(_cg, &x, &y);
		DrawBox(0, 0, screen_W, screen_W, GetColor(0, 0, 0), 1);
		DrawGraph(screen_W / 4-x/2, screen_H / 2-y/2, _cg, 0);
		DrawGraph(screen_W * 3 / 4-x/2, screen_H / 2-y/2, _cg, 0);
	}

}
