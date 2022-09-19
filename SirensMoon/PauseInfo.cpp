#include "PauseInfo.h"
#include "ModeGame.h"


PauseInfoA::PauseInfoA(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }
{
	_visible = true;
	_cg = ImageServer::LoadGraph("resource/UI/Pause/InfoRed.png");
}

void PauseInfoA::Update() {
}

void PauseInfoA::Render() {
	if (_visible) {
		DrawGraph(_pos.x, _pos.y, _cg, 1);
	}
}

PauseInfoB::PauseInfoB(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }
{
	_visible = true;
	_cg = ImageServer::LoadGraph("resource/UI/Pause/InfoBlue.png");
}

void PauseInfoB::Update() {
}

void PauseInfoB::Render() {
	if (_visible) {
		DrawGraph(_pos.x, _pos.y, _cg, 1);
	}
}