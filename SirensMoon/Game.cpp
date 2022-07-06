/*****************************************************************//**
 * \file   Game.cpp
 * \brief  プロセスを管理します。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#include "Game.h"
#include "ActorServer.h"

Game::Game()
{

	_inputManager = std::make_unique<InputManager>();
	_mapChips = std::make_unique<MapChips>(*this);

	_splitWindow.emplace_back(std::make_unique<SplitWindow>(*this, 0, 0,0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(*this, screen_W/2, 0,0));
	
	_actorServer = std::make_unique<ActorServer>();
	auto player0 = std::make_unique<Player>(*this,0);
	_actorServer->Add(std::move(player0));
	auto player1 = std::make_unique<Player>(*this, 1);
	_actorServer->Add(std::move(player1));
}

void Game::Input() {
	_inputManager->InputUpdate();
}
void Game::Update() {
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Update();
		_actorServer->Update();
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