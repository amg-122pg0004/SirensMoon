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
	:UIBase{ game,mode,pos,size },_delay{30},_changemode{false}
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/Pause/left.png");
	_cg2 = ImageServer::LoadGraph("resource/UI/Pause/right.png");
	
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
	if(dynamic_cast<ModeGame&>(_mode).)
	if (_visible){
		if (!_changemode) {
			if (_inputManager->CheckInput("BULLET1", 't', 0) ||
				_inputManager->CheckInput("BULLET1", 't', 1)) {
				_game.PlayStartMenu();
				_changemode = true;
			}
			if (_inputManager->CheckInput("BULLET2", 't', 0) ||
				_inputManager->CheckInput("BULLET2", 't', 1)) {
				_game.PlayStage1Clear();
				_changemode = true;
			}
			if (_inputManager->CheckInput("DEBUG", 't', 0) ||
				_inputManager->CheckInput("DEBUG", 't', 1)) {
				_game.PlayStage2Clear();
				_changemode = true;
			}
		}
	}

}

void Pause::Render() {
	if (_visible) {
		DrawGraph(0, 0, _cg, 1);
		DrawGraph(screen_W-splitscreen_W,0,_cg2, 1);
	}

}
