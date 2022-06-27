/*****************************************************************//**
 * \file   SplitWindow.cpp
 * \brief  分割画面内へのレンダリングを行うクラスです。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include <DxLib.h>
#include "SplitWindow.h"

SplitWindow::SplitWindow(Game& game,int pos_x, int pos_y,int playernum) :
	_game{game},_windowPos { pos_x ,pos_y},_playerNum{playernum}
{
	_camera = std::make_unique<Camera>(_game,*this);
	_windowSize_H = screen_H;
	_windowSize_W = screen_W / 2 - 30;
}

void SplitWindow::Update() {
	_camera->Update(_playerNum);
}

void SplitWindow::Render() {
	SetDrawArea(static_cast<int>(_windowPos.x),
		static_cast<int>(_windowPos.y), 
		static_cast<int>(_windowPos.x+ _windowSize_W),
		static_cast<int>(_windowPos.y + _windowSize_H));

	_game.GetMapChip()->Render(_windowPos,_camera->GetCameraPosition());
	_camera->Render(_windowPos.x + 50, _windowPos.y + 50);
	SetDrawArea(0,0,screen_W,screen_H);
}




