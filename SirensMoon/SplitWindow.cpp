/*****************************************************************//**
 * \file   SplitWindow.cpp
 * \brief  ������ʓ��ւ̕`����s���N���X�ł��B
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/

#include "SplitWindow.h"
#include "MapChip.h"
#include "ModeGame.h"
#include "MiniMap.h"
#include "Pause.h"
#include "ServerMachine.h"

SplitWindow::SplitWindow(Game& game,ModeBase& mode,int pos_x, int pos_y,int window_no) :
	_game{game}, _mode{mode}, _windowPos{pos_x ,pos_y}, _windowNo{window_no}, _renderStage{1},_lightup{255}
{
	_camera = std::make_unique<Camera>(_game,_mode,*this);
	_windowSize_H = screen_H;
	_windowSize_W = screen_W / 2;
	_darkness = std::make_unique<Darkness>(_game,_mode,*this);
	_darknessScreen = _darkness->MakeDarkness();
	_normalScreen = MakeScreen(screen_W, screen_H, 1);

	auto player = std::make_unique<Player>(_game,_mode,window_no);
	_mode.GetActorServer().Add(std::move(player));

	if (_windowNo == 1) {
		Vector2 map_pos = { 1080,0 };
		Vector2 map_size = { 780,600 };
		_ui.emplace_back(std::make_unique<MiniMap>(_game, _mode, map_pos, map_size));
	}

	Vector2 pause_pos = { 1080,0 };
	Vector2 pause_size = { 780,600 };
	_ui.emplace_back(std::make_unique<Pause>(_game, _mode, pause_pos, pause_size));
	
}

void SplitWindow::Update() {
	for (auto&& u : _ui) {
		u->Update();
	}
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::Server) {
			ServerMachine& machine  =dynamic_cast<ServerMachine&>(*actor);
			/*�A�Ŏd�l�ȑO�̕�
			if (machine.GetValidFlag()) {
				--_lightup;
				if (_lightup < 100) {
					_lightup = 100;
				}
			}
			else {
				_lightup =_lightup+ 20;
				if (_lightup > 255) {
					_lightup = 255;
				}
			}
			*/
			_lightup =255- machine.GetEnergy();//<�A�Ŏd�l
			if (_lightup < 100) {
				_lightup = 100;
			}
		}
	}
}

void SplitWindow::Render() {

	_darkness->Update(_windowPos, _camera->GetPosition());

	SetDrawScreen(_normalScreen);
	ClearDrawScreen();
	/*�`��͈͂𕪊���ʔ͈͂ɐݒ�*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y),
		static_cast<int>(_windowPos.x + _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));

	/*�w�i�`��*/
	static_cast<ModeGame&>(_mode).GetMapChips()->StandardRender(_renderStage - 1, _windowPos, _camera->GetPosition());
	/*�A�N�^�[�`��*/
	_mode.GetActorServer().StandardRender(_renderStage, _windowPos, _camera->GetPosition());

	GraphBlend(_normalScreen, _darknessScreen, _lightup, DX_GRAPH_BLEND_MULTIPLE);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, _normalScreen, 1);

	for (auto&& u : _ui) {
		u->Render();
	}

	//_camera->Render(static_cast<int>(_windowPos.x + 50),static_cast<int>(_windowPos.y + 50));
	/*�`��͈͂��E�B���h�E�T�C�Y�S�̂ɖ߂�*/
	SetDrawArea(0,0,screen_W,screen_H);
}

void SplitWindow::ChangeRenderStage(int changedelta) {
	_renderStage += changedelta;
}

void SplitWindow::Debug(){
	/*�`��͈͂𕪊���ʔ͈͂ɐݒ�*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y),
		static_cast<int>(_windowPos.x + _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));
	_mode.GetActorServer().Debug(_renderStage, _windowPos, _camera->GetPosition());
	std::stringstream ss;
	auto pos =_camera->GetPosition();
	ss << "�J����x" << pos.x << "�J����y" << pos.y;
	DrawString(50 + _windowNo * 960, 300, ss.str().c_str(), GetColor(255, 0, 255));
	/*�`��͈͂��E�B���h�E�T�C�Y�S�̂ɖ߂�*/
	SetDrawArea(0, 0, screen_W, screen_H);
}
