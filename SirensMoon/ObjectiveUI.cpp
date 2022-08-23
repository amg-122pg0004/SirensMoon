#include "ObjectiveUI.h"
#include <sstream>

ObjectiveUI::ObjectiveUI(Game& game,ModeBase& mode,Vector2 pos,Vector2 size)
	:UIBase(game, mode, pos, size),
	_message{ "ミニマップ上のサーバーへ向かう" },
	_nextMessage{ "NULL" }, _startPos{ pos }
{
	_cg2= ImageServer::LoadGraph("resource/UI/Objective/green.png");
	_font=CreateFontToHandle("ObjectiveFont",20,5,-1);
	_cg = ImageServer::LoadGraph("resource/UI/Objective/orange.png");

	_pos = { _pos.x - _size.x,_pos.y - 10 };
}

void ObjectiveUI::Update(){
	/*//切り替え型
	if (_nextMessage != "NULL"&&_nextMessage!=_message) {
		if (_startPos.x - _pos.x < _size.x+15) {
			_pos.x -= 15;
		}
		if (_startPos.x - _pos.x >= _size.x) {
			_message = _nextMessage;
			_nextMessage = "NULL";
		}
		return;
	}
	if (_pos.x < _startPos.x) {
		_pos.x += 15;
	}
	*/
	if (_nextMessage != "NULL") {
		if (_pos.x < _startPos.x-5) {
			_pos.x += 15;
		}
	}
	else {
		if (_pos.x > _startPos.x - _size.x) {
			_pos.x -= 15;
		}
	}
}

void ObjectiveUI::Render() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
	DrawGraph(static_cast<int>(_startPos.x), static_cast<int>(_startPos.y),_cg,1);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg2, 1);
	
	std::stringstream ss,ss2;
	ss << _message;
	ss2 << _nextMessage;
	DrawStringToHandle(static_cast<int>(_startPos.x+10), static_cast<int>(_startPos.y + 25), ss.str().c_str(), GetColor(255, 255, 255), _font);
	DrawStringToHandle(static_cast<int>(_pos.x + 10), static_cast<int>(_pos.y + 25), ss2.str().c_str(), GetColor(255, 255, 255), _font);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ObjectiveUI::ChangeMessage(std::string next){
	_nextMessage = next;
}