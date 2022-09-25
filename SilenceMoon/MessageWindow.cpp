#include "MessageWindow.h"
#include "Game.h"
#include "ModeGame.h"
#include "DegitalLetter.h"
#include <sstream>

class SplitWindow;

MessageWindow::MessageWindow(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size,int playerno)
	:UIBase(game,mode, window, pos,size),_message{},_alpha{0},_image{-1}
{
	_cg = ImageServer::LoadGraph("resource/UI/DegialLetter/degitalletter.png");
	_font = LoadFontDataToHandle("resource/Font/ロンドBスクエア26.dft", 1);
	_playerno = playerno;
	_imageWindow= ImageServer::LoadGraph("resource/UI/DegialLetter/degitalletterMini.png");
}

void MessageWindow::Update() {
	bool triggerflag{ 0 };
	bool overlapflag{ 0 };
	for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
		if (actor->GetType() == Actor::Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::DegitalLetter) {
				if (_playerno == 0) {
					if (dynamic_cast<DegitalLetter&>(*actor).GetAccessible1()) {
						overlapflag = true;
						if (_game.GetInputManager()->CheckInput("ACCESS", 't', _playerno)) {
							triggerflag=true;
						}
					}
				}
				else {
					if (dynamic_cast<DegitalLetter&>(*actor).GetAccessible2()) {
						overlapflag = true;
						if (_game.GetInputManager()->CheckInput("ACCESS", 't', _playerno)) {
							triggerflag = true;;
						}
					}
				}
			}
		}
	}
	if (!overlapflag) {
		_visible = false;
	}
	if (triggerflag) {
		_visible = !_visible;
	}

	else {

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
}

void MessageWindow::Render()
{
	if (!_message.empty()) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 0);
		if (_image != -1) {
			DrawGraph(static_cast<int>(_pos.x + 650), static_cast<int>(_pos.y - 100), _imageWindow, 0);
			DrawRotaGraph(static_cast<int>(_pos.x + 650+95), static_cast<int>(_pos.y - 100+90),1.0,0.0,_image, 1);
		}


		std::stringstream ss;
		ss << _message;
		Vector2 fix{ 50,50 };
		DrawStringToHandle(static_cast<int>(_pos.x+fix.x), static_cast<int>(_pos.y+fix.y), ss.str().c_str(), GetColor(255, 255, 255), _font);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void MessageWindow::SetMessage(std::string msg,int image){
	if (_message != msg) {
		_message = msg;
		_image = image;
	}
}
