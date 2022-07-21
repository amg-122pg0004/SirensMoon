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

SplitWindow::SplitWindow(Game& game,ModeBase& mode,int pos_x, int pos_y,int window_no) :
	_game{game}, _mode{mode}, _windowPos{pos_x ,pos_y}, _windowNo{window_no}, _renderStage{1}
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
}

void SplitWindow::Render() {

	_darkness->Update(_windowPos, _camera->GetPosition());

	SetDrawScreen(_normalScreen);
	/*描画範囲を分割画面範囲に設定*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y),
		static_cast<int>(_windowPos.x + _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));


	static_cast<ModeGame&>(_mode).GetMapChips()->StandardRender(_renderStage - 1, _windowPos, _camera->GetPosition());
	_mode.GetActorServer().StandardRender(_renderStage, _windowPos, _camera->GetPosition());

	GraphBlend(_normalScreen, _darknessScreen, 255, DX_GRAPH_BLEND_MULTIPLE);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, _normalScreen, 1);

	for (auto&& u : _ui) {
		u->Render();
	}

	//_camera->Render(static_cast<int>(_windowPos.x + 50),static_cast<int>(_windowPos.y + 50));
	/*描画範囲をウィンドウサイズ全体に戻す*/
	SetDrawArea(0,0,screen_W,screen_H);
}

void SplitWindow::ChangeRenderStage(int changedelta) {
	_renderStage += changedelta;
}

void SplitWindow::Debug(){
	/*描画範囲を分割画面範囲に設定*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y),
		static_cast<int>(_windowPos.x + _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));
	_mode.GetActorServer().Debug(_renderStage, _windowPos, _camera->GetPosition());
	/*描画範囲をウィンドウサイズ全体に戻す*/
	SetDrawArea(0, 0, screen_W, screen_H);
}
