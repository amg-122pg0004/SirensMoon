#include "MessageWindow.h"
#include "Game.h"
#include <sstream>

MessageWindow::MessageWindow(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase(game,mode,pos,size),_message{}
{
	_cg = ImageServer::LoadGraph("resource/UI/DegialLetter/degitalletter.png");
	_font = CreateFontToHandle("ObjectiveFont", 20, 5, -1);
}

void MessageWindow::Update()
{

}

void MessageWindow::Render()
{
	if (!_message.empty()) {
		DrawGraph((splitscreen_W-_size.x)/2,screen_H-_size.y,_cg,0);

		std::stringstream ss;
		ss << _message;
		DrawStringToHandle(static_cast<int>(_pos.x + 10), static_cast<int>(_pos.y + 25), ss.str().c_str(), GetColor(255, 255, 255), _font);
	}
}

void MessageWindow::SetMessage(std::string msg){
	_message = msg;
}
