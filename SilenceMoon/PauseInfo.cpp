#include "PauseInfo.h"
#include "ModeGame.h"
class SplitWindow;

PauseInfoA::PauseInfoA(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size }
{
	_visible = true;
	_cg = ImageServer::LoadGraph("resource/UI/Pause/InfoRed.png");
}

void PauseInfoA::Update() {
}

void PauseInfoA::Render() {
	if (_visible) {
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 1);
	}
}

PauseInfoB::PauseInfoB(Game& game, ModeBase& mode,SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size }
{
	_visible = true;
	_cg = ImageServer::LoadGraph("resource/UI/Pause/InfoBlue.png");
}

void PauseInfoB::Update() {
}

void PauseInfoB::Render() {
	if (_visible) {
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 1);
	}
}