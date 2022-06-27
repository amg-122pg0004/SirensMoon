/*****************************************************************//**
 * \file   Game.cpp
 * \brief  プロセスを管理します。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#include <DxLib.h>
#include <memory>
#include "Game.h"

Game::Game() {

	_inputManager = std::make_unique<InputManager>();
	_mapChip = std::make_unique<MapChip>(*this);
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(*this, 0, 0,0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(*this, screen_W/2+30, 0,1));
}

void Game::Input() {
	_inputManager->InputUpdate();
}
void Game::Update() {
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Update();
	}
}
void Game::Render() {
	ClearDrawScreen();
	
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Render();
	}
	_inputManager->Render();
	

	ScreenFlip();
}
