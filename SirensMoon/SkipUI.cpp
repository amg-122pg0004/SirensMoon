#include "SkipUI.h"
#include "ModeGame.h"


SkipUI::SkipUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }, _animNo{ 0 }
{
	_visible = false;
	_cg.resize(89);
	ImageServer::LoadDivGraph("resource/UI/Skip/blue.png", 89, 8, 11, 163, 163, _cg.data());
	_cg2.resize(89);
	ImageServer::LoadDivGraph("resource/UI/Skip/blue.png", 89, 8, 11, 163, 163, _cg2.data());
}

void SkipUI::Update() {
	if (!_visible) {
		return;
	}
	++_animNo;
	if (_animNo >= _cg.size()-1) {
		_animNo = 0;
		_visible = false;
	}
}

void SkipUI::Render() {
	if (_visible) {
		DrawGraph(_pos.x, _pos.y, _cg[_animNo], 1);
		DrawGraph(_pos.x + splitscreen_W, _pos.y, _cg2[_animNo], 1);
	}
}

void SkipUI::SetVisibillity(bool flag) {
	if (flag) {
		_visible = 0;
	}
	_visible = flag;
}