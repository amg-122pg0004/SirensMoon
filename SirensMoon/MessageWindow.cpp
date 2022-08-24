#include "MessageWindow.h"
#include "Game.h"
#include "ModeGame.h"
#include "DegitalLetter.h"
#include <sstream>

MessageWindow::MessageWindow(Game& game, ModeBase& mode, Vector2 pos, Vector2 size,int playerno)
	:UIBase(game,mode,pos,size),_message{},_alpha{0}
{
	_cg = ImageServer::LoadGraph("resource/UI/DegialLetter/degitalletter.png");
	_font = CreateFontToHandle("ObjectiveFont", 20, 9, -1);
	_playerno = playerno;
}

void MessageWindow::Update()
{
	for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
		if (actor->GetType() == Actor::Type::Gimmick) {
			if(dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::DegitalLetter) {
				if (_playerno==0) {
					if (dynamic_cast<DegitalLetter&>(*actor).GetAccessible1()) {
						if (_game.GetInputManager()->CheckInput("ACCESS", 't', _playerno)) {
							_visible = !_visible;
						}
					}
					else {
						_visible = false;
					}
				}
				else {
					if (dynamic_cast<DegitalLetter&>(*actor).GetAccessible2()) {
						if (_game.GetInputManager()->CheckInput("ACCESS", 't', _playerno)) {
							_visible = !_visible;
						}
					}
					else {
						_visible = false;
					}
				}
			}
		}
	}

	if (_visible) {
		_alpha += 30;
		if (_alpha > 255) {
			_alpha = 255;
		}
	}
	else {
		_alpha -= 30;
		if (_alpha < 0) {
			_alpha = 0;
		}
	}
}

void MessageWindow::Render()
{
	if (!_message.empty()) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawGraph(_pos.x,_pos.y,_cg,0);

		std::stringstream ss;
		ss << _message;
		Vector2 fix{ 50,50 };
		DrawStringToHandle(static_cast<int>(_pos.x+fix.x), static_cast<int>(_pos.y+fix.y), ss.str().c_str(), GetColor(255, 255, 255), _font);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void MessageWindow::SetMessage(std::string msg){
	if (_message != msg) {
		_message = msg;
	}
}
