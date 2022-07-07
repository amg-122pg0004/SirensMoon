/*****************************************************************//**
 * \file   SplitWindow.cpp
 * \brief  分割画面内へのレンダリングを行うクラスです。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "SplitWindow.h"
#include "MapChip.h"

SplitWindow::SplitWindow(Game& game,int pos_x, int pos_y,int window_no) :
	_game{ game }, _windowPos{ pos_x ,pos_y }, _windowNo{window_no}, _renderStage{ 1 }
{
	_camera = std::make_unique<Camera>(_game,*this);
	_windowSize_H = screen_H;
	_windowSize_W = screen_W / 2;
	_darkness = std::make_unique<Darkness>(_game,*this);
	_darknessScreen = _darkness->MakeDarkness();
	_normalScreen = MakeScreen(screen_W, screen_H, 1);

	auto player = std::make_unique<Player>(_game, _windowNo);
	_game.GetActorServer()->Add(std::move(player));
}

void SplitWindow::Update() {

}

void SplitWindow::Render() {
	/*描画範囲を分割画面範囲に設定*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y), 
		static_cast<int>(_windowPos.x+ _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));



		_darkness->Update(_windowPos, _camera->GetPosition());
		SetDrawScreen(_normalScreen);
		ClearDrawScreen();
		_game.GetMapChips()->StandardRender(_renderStage - 1, _windowPos, _camera->GetPosition());
		_game.GetActorServer()->StandardRender(_renderStage, _windowPos, _camera->GetPosition());
		GraphBlend(_normalScreen, _darknessScreen, 255, DX_GRAPH_BLEND_MULTIPLE);
		SetDrawScreen(DX_SCREEN_BACK);
		DrawGraph(0, 0, _normalScreen, 1);


	_camera->Render(static_cast<int>(_windowPos.x + 50),static_cast<int>(_windowPos.y + 50));
	/*描画範囲をウィンドウサイズ全体に戻す*/
	SetDrawArea(0,0,screen_W,screen_H);
}

void SplitWindow::ChangeRenderStage(int changedelta) {
	_renderStage += changedelta;
}