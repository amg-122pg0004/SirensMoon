#include "ObjectiveUI.h"
#include "Game.h"
#include <sstream>
class SplitWindow;
ObjectiveUI::ObjectiveUI(Game& game,ModeBase& mode, SplitWindow& window, Vector2 pos,Vector2 size)
	:UIBase(game, mode, window, pos, size),
	_message{ "ミニマップ上に黄色い点で\n示されたサーバーへ向かう" },
	_nextMessage{ "NULL" }, _startPos{ pos }
{
	_font = LoadFontDataToHandle("resource/Font/ロンドBスクエア.dft", 1);
	_cgOrange = ImageServer::LoadGraph("resource/UI/Objective/orange.png");
	_cgGreen = ImageServer::LoadGraph("resource/UI/Objective/green.png");
	_cgRed1 = ImageServer::LoadGraph("resource/UI/Objective/red1.png");
	_cgRed2 = ImageServer::LoadGraph("resource/UI/Objective/red2.png");

	_cg = _cgOrange;
	_nextCG = _cgOrange;
}

void ObjectiveUI::Update(){

}

void ObjectiveUI::Render() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),_cg,1);
	
	std::stringstream ss;
	ss << _message;
	DrawStringToHandle(static_cast<int>(_pos.x+10), static_cast<int>(_pos.y + 25), ss.str().c_str(), GetColor(255, 255, 255), _font);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ObjectiveUI::ChangeMessage(std::string next, int nextCGColor) {
	_nextMessage = next;
	switch (nextCGColor) {
	case(1):
	default:
		_nextCG = _cgOrange;
		break;
	case(2):
		_nextCG = _cgGreen;
		break;
	}
}

void ObjectiveUI::ChangeWarning(int no) {
	_nextMessage = " ";
	if (no == 0) {
		_nextCG = _cgRed1;
	}
	else {
		_nextCG = _cgRed2;
	}
}

/*1プレイヤー用UI*/
ObjectiveUI1::ObjectiveUI1(Game& game, ModeBase& mode,SplitWindow& window, Vector2 pos, Vector2 size)
	:ObjectiveUI(game, mode, window, pos, size)
{
}

void ObjectiveUI1::Update() {
	if (_nextMessage != "NULL" && _nextMessage != _message) {
		if (_startPos.x - _pos.x < _size.x + 15) {
			_pos.x -= 15;
		}
		if (_startPos.x - _pos.x >= _size.x) {
			_message = _nextMessage;
			_nextMessage = "NULL";
			_cg = _nextCG;
		}
		return;
	}
	if (_pos.x < _startPos.x) {
		_pos.x += 15;
	}
}

/*2プレイヤー用UI*/
ObjectiveUI2::ObjectiveUI2(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:ObjectiveUI(game, mode, window, pos, size)
{
}

void ObjectiveUI2::Update() {
	if (_nextMessage != "NULL" && _nextMessage != _message) {
		if (_pos.y < _startPos.y +_size.y + 25) {
			_pos.y += 5;
		}
		if (_pos.y >= _startPos.y + _size.y + 25) {
			_message = _nextMessage;
			_nextMessage = "NULL";
			_cg = _nextCG;
		}
		return;
	}
	if (_pos.y > _startPos.y) {
		_pos.y -= 5;
	}
}