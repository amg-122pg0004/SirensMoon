/*****************************************************************//**
 * \file   SplitWindow.cpp
 * \brief  分割画面内への描画を行うクラスです。
 *
 * \author 土居将太郎
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
#include "FoundUI.h"
#include "ButtonIcon.h"
#include "ObjectiveUI.h"
#include "MessageWindow.h"
#include "FinishCut.h"

SplitWindow::SplitWindow(Game& game, ModeGame& mode, int pos_x, int pos_y, int window_no) :
	_game{ game }, _mode{ mode }, _windowPos{ pos_x ,pos_y }, _windowNo{ window_no }, _renderStage{ 1 }, _lightup{ 255 }
{
	_camera = std::make_unique<Camera>(_game, _mode, *this);
	_windowSize_H = screen_H;
	_windowSize_W = splitscreen_W;
	_darkness = std::make_unique<Darkness>(_game, _mode, *this);
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
		Vector2 map_pos = { _windowPos.x + 90,_windowPos.y - 5 };
		Vector2 map_size = { 480,180 };
		_ui.emplace_back(std::make_unique<AmmoUI>(_game, _mode, map_pos, map_size));

		Vector2 bullettype_pos = { _windowPos.x + 5,_windowPos.y + 5 };
		Vector2 bullettype_size = { 90,180 };
		_ui.emplace_back(std::make_unique<BulletTypeUI>(_game, _mode, bullettype_pos, bullettype_size));
	}

	Vector2 found_pos = { 0,0 };
	Vector2 found_size = { 90,60 };
	_ui.emplace_back(std::make_unique<FoundUI>(_game, _mode, found_pos, found_size, _windowNo));

	Vector2 button_pos = { 0,0 };
	Vector2 button_size = { 60,60 };
	_ui.emplace_back(std::make_unique<ButtonIcon>(_game, _mode, button_pos, button_size, _windowNo));

	Vector2 hp_pos = { _windowPos.x ,screen_H - 270 };
	Vector2 hp_size = { 90,270 };
	_ui.emplace_back(std::make_unique<HPUI>(_game, _mode, hp_pos, hp_size, _windowNo));

	Vector2 obj_size = { 360 + 30,90 };
	Vector2 obj_pos = { _windowPos.x + splitscreen_W * 0.6, screen_H * 0.9 };
	auto obj_ui=std::make_unique<ObjectiveUI2>(_game, _mode, obj_pos, obj_size);
	_objectiveUI = obj_ui.get();
	_ui.emplace_back(std::move(obj_ui));

	if (_windowNo == 1) {
		Vector2 map_pos = { _windowPos.x + splitscreen_W / 2 - 780 / 2, _windowPos.y };
		Vector2 map_size = { 780,600 };
		_ui.emplace_back(std::make_unique<MiniMap>(_game, _mode, map_pos, map_size));
	}


	Vector2 message_size = { 870,180 };
	Vector2 message_pos = { _windowPos.x+(splitscreen_W-message_size.x)/2 ,_windowPos.y + screen_H - message_size.y };
	_ui.emplace_back(std::make_unique<MessageWindow>(_game, _mode, message_pos, message_size,window_no));


	double damage_scale = 840.0 / 320.0;
	Vector2 damage_pos = { _windowPos.x,(screen_H - 840) / 2 };
	Vector2 damage_size = { 640 * damage_scale,840 };
	_ui.emplace_back(std::make_unique<DamageCut>(_game, _mode, damage_pos, damage_size));

	
	Vector2 special_pos = { _windowPos.x,(screen_H - 840) / 2 };
	Vector2 special_size = { 640,840 };
	_ui.emplace_back(std::make_unique<FinishCut>(_game, _mode, special_pos, special_size));
	

	Vector2 pause_pos = { _windowPos.x + splitscreen_W / 2, _windowPos.y };
	Vector2 pause_size = { 360,90 };
	_ui.emplace_back(std::make_unique<Pause>(_game, _mode, pause_pos, pause_size));

}

SplitWindow::~SplitWindow() {
	DeleteGraph(_darknessScreen);
	DeleteGraph(_normalScreen);
}

void SplitWindow::Update() {
	/*透明ポンプギミック用の処理*/
	--_blindTimer;
	if (_blindTimer < 0) {
		_blindTimer = 0;
		_invisiblePlayer = false;
	}
	/*サーバーアクセス時にマップ全体が明るくなる処理*/
	_lightup = 255;
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::Server) {
			ServerMachine& machine = dynamic_cast<ServerMachine&>(*actor);
			/*連打仕様以前の物
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
				_lightup = 255 - machine.GetEnergy();//<連打仕様
			}

			if (_lightup < 100) {
				_lightup = 100;
			}
		}
	}
	for (auto&& u : _ui) {
		u->Update();
	}
}

void SplitWindow::Render() {

	_darkness->Update(_windowPos, _camera->GetPosition());

	SetDrawScreen(_normalScreen);
	ClearDrawScreen();
	/*描画範囲を分割画面範囲に設定*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y),
		static_cast<int>(_windowPos.x + _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));

	/*奥背景描画*/
	static_cast<ModeGame&>(_mode).GetMapChips()->Render(_windowPos, _camera->GetPosition(), "back");
	/*奥アクター描画*/
	_mode.GetActorServer().BackRender(_windowPos, _camera->GetPosition());
	/*通常背景描画*/
	static_cast<ModeGame&>(_mode).GetMapChips()->Render(_windowPos, _camera->GetPosition(),"middle");
	/*アクター描画*/
	_mode.GetActorServer().StandardRender(_windowPos, _camera->GetPosition(),*this);
	/*手前背景描画*/
	static_cast<ModeGame&>(_mode).GetMapChips()->Render(_windowPos, _camera->GetPosition(),"front");

	GraphBlend(_normalScreen, _darknessScreen, 100, DX_GRAPH_BLEND_SCREEN);
	GraphBlend(_normalScreen, _darknessScreen, _lightup+120, DX_GRAPH_BLEND_MULTIPLE);


	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, _normalScreen, 1);
	/*描画範囲を分割画面範囲に設定*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y),
		static_cast<int>(_windowPos.x + _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));
	for (auto&& u : _ui) {
		u->Render();
	}

	//_camera->Render(static_cast<int>(_windowPos.x + 50),static_cast<int>(_windowPos.y + 50));
	/*描画範囲をウィンドウサイズ全体に戻す*/
	SetDrawArea(static_cast<int>(_windowPos.x), 0, splitscreen_W, screen_H);
}

void SplitWindow::Debug() {
	/*描画範囲を分割画面範囲に設定*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y),
		static_cast<int>(_windowPos.x + _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));
	_mode.GetActorServer().Debug(_renderStage, _windowPos, _camera->GetPosition());
	std::stringstream ss;
	auto pos = _camera->GetPosition();
	ss << "カメラx" << pos.x << "カメラy" << pos.y;
	ss << "ライトアップ" << _lightup;
	DrawString(50 + _windowNo * 960, 300, ss.str().c_str(), GetColor(255, 0, 255));
	/*描画範囲をウィンドウサイズ全体に戻す*/
	SetDrawArea(0, 0, screen_W, screen_H);
}

void SplitWindow::DamageEvent() {
	for (auto&& u : _ui) {
		u->DamageEvent();
	}
}

void SplitWindow::TargetKillEvent() {
	for (auto&& u : _ui) {
		u->TargetKillEvent();
	}
}

void SplitWindow::ScreenPumpEvent(){
	if (!_invisiblePlayer) {
		_blindTimer = 30 * 60;
		_invisiblePlayer = true;
	}
}
