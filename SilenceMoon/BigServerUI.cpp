/*****************************************************************//**
 * \file   BigServerUI.cpp
 * \brief  ボス第2フェーズ時、モールス信号を表示するUI
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "BigServerUI.h"
#include <sstream>
#include "BigServer.h"
#include "Game.h"

class SplitWindow;

BigServerUI::BigServerUI(Game& game , ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size, BigServer& owner)
:UIBase(game,mode, window, pos,size),_owner{owner}
{
	_cg = ImageServer::LoadGraph("resource/UI/wanted.png");
	_cg_gun= ImageServer::LoadGraph("resource/Gimmick/biggun.png");
	_font = _game.GetFont22();
}

void BigServerUI::Update(){
	if (_owner.GetAccessible()) {
		if(_game.GetInputManager()->CheckInput("ACCESS", 't', 1)) {
			_visible = !_visible;
		}
	}
	else {
		_visible = false;
	}
}

void BigServerUI::Render(){

	if (_visible) {
		SetDrawArea(0,0,screen_W,screen_H);
		auto pattern=_owner.GetPattern();
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 0);
		DrawExtendGraph(static_cast<int>(_pos.x+25), static_cast<int>(_pos.y+100)
			, static_cast<int>(_pos.x + 25+250), static_cast<int>(_pos.y + 100+250),
			_cg_gun, 1);

		std::stringstream ss;
		ss <<"１　　" << _text[pattern[0]] << "\n";
		ss <<"２　　" << _text[pattern[1]] << "\n";
		ss <<"３　　" << _text[pattern[2]] << "\n";
		ss <<"４　　" << _text[pattern[3]] << "\n";

		DrawStringToHandle(static_cast<int>(_pos.x+300), static_cast<int>(_pos.y+220),
			ss.str().c_str(), GetColor(255, 255, 255), _font);
	}
}
