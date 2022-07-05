/*****************************************************************//**
 * \file   SplitWindow.cpp
 * \brief  分割画面内へのレンダリングを行うクラスです。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "SplitWindow.h"
#include "MapChip.h"

SplitWindow::SplitWindow(Game& game,int pos_x, int pos_y,bool reconflag) :
	_game{ game }, _windowPos{ pos_x ,pos_y }, _reconFlag{reconflag}, _renderStage{ 1 }
{
	_camera = std::make_unique<Camera>(_game,*this);
	_windowSize_H = screen_H;
	_windowSize_W = screen_W / 2;
	_darkness = std::make_unique<Darkness>(_game);
}

void SplitWindow::Update() {
	//_camera->Update(_playerNum);
}

void SplitWindow::Render() {
	/*描画範囲を分割画面範囲に設定*/
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y), 
		static_cast<int>(_windowPos.x+ _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));

	if (_reconFlag) {
		_game.GetMapChips()->ReconRender(_renderStage - 1, _windowPos, _camera->GetCameraPosition());
		_game.GetActorServer()->ReconRender(_renderStage, _windowPos, _camera->GetCameraPosition());
	}
	else {
		_darknessScreen = _darkness->MakeDarkness();
		int handle=MakeScreen(screen_W,screen_H,1);
		//SetDrawScreen(handle);
		_game.GetMapChips()->StandardRender(_renderStage - 1, _windowPos, _camera->GetCameraPosition());
		_game.GetActorServer()->StandardRender(_renderStage, _windowPos, _camera->GetCameraPosition());
		
		//GraphBlend(handle, _darknessScreen, 255, DX_GRAPH_BLEND_NORMAL);

		//DrawGraph(0, 0, handle, 1);

	}

	_camera->Render(static_cast<int>(_windowPos.x + 50),static_cast<int>(_windowPos.y + 50));
	/*描画範囲をウィンドウサイズ全体に戻す*/
	SetDrawArea(0,0,screen_W,screen_H);
}

void SplitWindow::ChangeRenderStage(int changedelta) {
	_renderStage += changedelta;
}