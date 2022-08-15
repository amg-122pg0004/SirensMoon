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
#include "HPUI.h"
#include "AmmoUI.h"
#include "BulletTypeUI.h"
#include "DamageCut.h"

SplitWindow::SplitWindow(Game& game,ModeGame& mode,int pos_x, int pos_y,int window_no) :
	_game{game}, _mode{mode}, _windowPos{pos_x ,pos_y}, _windowNo{window_no}, _renderStage{1},_lightup{255}
{
	_camera = std::make_unique<Camera>(_game,_mode,*this);
	_windowSize_H = screen_H;
	_windowSize_W = splitscreen_W;
	_darkness = std::make_unique<Darkness>(_game,_mode,*this);
	_darknessScreen = _darkness->MakeDarkness();
	_normalScreen = MakeScreen(screen_W, screen_H, 1);

	if (window_no == 0) {
		auto player = std::make_unique<PlayerA>(_game, _mode, window_no);
		_mode.GetActorServer().Add(std::move(player));
	}
	else {
		auto player = std::make_unique<PlayerB>(_game, _mode, window_no);
		_mode.GetActorServer().Add(std::move(player));
	}

	if (_windowNo == 0) {
		Vector2 map_pos = { _windowPos.x+90,_windowPos.y -5 };
		Vector2 map_size = { 480,180 };
		_ui.emplace_back(std::make_unique<AmmoUI>(_game, _mode, map_pos, map_size));

		Vector2 bullettype_pos = { _windowPos.x + 5,_windowPos.y+5 };
		Vector2 bullettype_size = { 90,180 };
		_ui.emplace_back(std::make_unique<BulletTypeUI>(_game, _mode, bullettype_pos, bullettype_size));

		Vector2 hp_pos = { splitscreen_W-90,screen_H-270 };
		Vector2 hp_size = { 90,270 };
		_ui.emplace_back(std::make_unique<HPUI>(_game, _mode, hp_pos, hp_size, _windowNo));
	}

	if (_windowNo == 1) {
		Vector2 map_pos = {_windowPos.x + splitscreen_W / 2-780/2, _windowPos.y};
		Vector2 map_size = { 780,600 };
		_ui.emplace_back(std::make_unique<MiniMap>(_game, _mode, map_pos, map_size));

		Vector2 hp_pos = { _windowPos.x ,screen_H - 270 };
		Vector2 hp_size = { 90,270 };
		_ui.emplace_back(std::make_unique<HPUI>(_game, _mode, hp_pos, hp_size, _windowNo));
	}

	Vector2 pause_pos = { _windowPos.x + splitscreen_W / 2, _windowPos.y };
	Vector2 pause_size = { 780,600 };
	_ui.emplace_back(std::make_unique<Pause>(_game, _mode, pause_pos, pause_size));

	double damage_scale = 840 / 320;
	Vector2 damage_pos = { _windowPos.x, _windowPos.y+screen_H/2-320 * damage_scale/2 };
	Vector2 damage_size = { 640 * damage_scale,320 * damage_scale };
	_ui.emplace_back(std::make_unique<DamageCut>(_game, _mode, damage_pos, damage_size));
	
}

void SplitWindow::Update() {
	for (auto&& u : _ui) {
		u->Update();
	}
	_lightup = 255;
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

			if (_lightup > 255 - machine.GetEnergy()) {
				_lightup = 255 - machine.GetEnergy();//<�A�Ŏd�l
			}

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
	_mode.GetActorServer().StandardRender(_windowNo, _windowPos, _camera->GetPosition());

	/*��O�w�i�`��*/
	static_cast<ModeGame&>(_mode).GetMapChips()->FrontRender(_renderStage - 1, _windowPos, _camera->GetPosition());

	GraphBlend(_normalScreen, _darknessScreen, _lightup, DX_GRAPH_BLEND_MULTIPLE);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, _normalScreen, 1);
	/*�`��͈͂𕪊���ʔ͈͂ɐݒ�*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y),
		static_cast<int>(_windowPos.x + _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));
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
	ss << "���C�g�A�b�v" << _lightup;
	DrawString(50 + _windowNo * 960, 300, ss.str().c_str(), GetColor(255, 0, 255));
	/*�`��͈͂��E�B���h�E�T�C�Y�S�̂ɖ߂�*/
	SetDrawArea(0, 0, screen_W, screen_H);
}

void SplitWindow::DamageEvent() {
	for (auto&& u : _ui) {
		u->DamageEvent();
	}
}
