/*****************************************************************//**
 * \file   Game.cpp
 * \brief  プロセスを管理します。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#include "Game.h"

Game::Game()
{
	_modeServer = std::make_unique<ModeServer>();
	_inputManager = std::make_unique<InputManager>();

	auto mode = std::make_unique<ModeGame>(*this);
	_modeServer->Add(std::move(mode));
}

void Game::Input() {
	_inputManager->InputUpdate();
}
void Game::Update() {
	_modeServer->Update();
}

void Game::Render() {
	_modeServer ->Render();
	
}

void Game::Debug(){
	_modeServer->Debug();
}
