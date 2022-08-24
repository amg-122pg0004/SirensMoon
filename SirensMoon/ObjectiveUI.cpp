#include "ObjectiveUI.h"
#include "Game.h"
#include <sstream>

ObjectiveUI::ObjectiveUI(Game& game,ModeBase& mode,Vector2 pos,Vector2 size)
	:UIBase(game, mode, pos, size),
	_message{ "ミニマップ上のサーバーへ向かう" },
	_nextMessage{ "NULL" }, _startPos{ pos }
{
	_font=CreateFontToHandle("ObjectiveFont",20,5,-1);
	_cg = ImageServer::LoadGraph("resource/UI/Objective/orange.png");
	_cg2 = ImageServer::LoadGraph("resource/UI/Objective/green.png");
	_cg3 = _cg;
}

void ObjectiveUI::Update(){

}

void ObjectiveUI::Render() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),_cg3,1);
	
	std::stringstream ss;
	ss << _message;
	DrawStringToHandle(static_cast<int>(_pos.x+10), static_cast<int>(_pos.y + 25), ss.str().c_str(), GetColor(255, 255, 255), _font);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ObjectiveUI::ChangeMessage(std::string next){
	_nextMessage = next;
}


/*1プレイヤー用UI*/
ObjectiveUI1::ObjectiveUI1(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:ObjectiveUI(game, mode, pos, size)
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
			if (_cg3 == _cg) {
				_cg3 = _cg2;
			}
			else {
				_cg3 = _cg;
			}
		}
		return;
	}
	if (_pos.x < _startPos.x) {
		_pos.x += 15;
	}
}

/*2プレイヤー用UI*/
ObjectiveUI2::ObjectiveUI2(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:ObjectiveUI(game, mode, pos, size)
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
			if (_cg3 == _cg) {
				_cg3 = _cg2;
			}
			else {
				_cg3 = _cg;
			}
		}
		return;
	}
	if (_pos.y > _startPos.y) {
		_pos.y -= 5;
	}
}