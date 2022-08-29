#include "BigServerUI.h"
#include <sstream>
#include "BigServer.h"
#include "Game.h"

BigServerUI::BigServerUI(Game& game , ModeBase& mode, Vector2 pos, Vector2 size, BigServer& owner)
:UIBase(game,mode,pos,size),_owner{owner}
{
	_cg = ImageServer::LoadGraph("resource/UI/wanted.png");
	_font = CreateFontToHandle("ObjectiveFont", 20, 9, -1);
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
		auto pattern=_owner.GetPattern();
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 0);

		std::stringstream ss;
		ss <<"‚P@@" << _text[pattern[0]] << "\n";
		ss <<"‚Q@@" << _text[pattern[1]] << "\n";
		ss <<"‚R@@" << _text[pattern[2]] << "\n";
		ss <<"‚S@@" << _text[pattern[3]] << "\n";

		DrawStringToHandle(static_cast<int>(_pos.x+300), static_cast<int>(_pos.y+220),
			ss.str().c_str(), GetColor(255, 255, 255), _font);
	}
}
