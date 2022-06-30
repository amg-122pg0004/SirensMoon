/*****************************************************************//**
 * \file   SplitWindow.cpp
 * \brief  分割画面内へのレンダリングを行うクラスです。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "SplitWindow.h"
#include "MapChip.h"

SplitWindow::SplitWindow(Game& game,int pos_x, int pos_y,int playernum) :
	_game{game},_windowPos { pos_x ,pos_y},_playerNum{playernum}
{
	_camera = std::make_unique<Camera>(_game,*this);
	_windowSize_H = screen_H;
	_windowSize_W = screen_W / 2 - 30;
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

	_game.GetMapChips()->Render(_windowPos,_camera->GetCameraPosition());
	_game.GetActorServer()->Render(_windowPos, _camera->GetCameraPosition());

	_camera->Render(static_cast<int>(_windowPos.x + 50),static_cast<int>(_windowPos.y + 50));
	/*描画範囲をウィンドウサイズ全体に戻す*/
	SetDrawArea(0,0,screen_W,screen_H);
}




