/*****************************************************************//**
 * \file   Game.cpp
 * \brief  プロセスを管理します。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#include "Game.h"
#include "ModeBase.h"
#include "ModeGame.h"
#include "ModeStart.h"

Game::Game() :_frameCount{0}
{
	_modeServer = std::make_unique<ModeServer>(*this);
	_inputManager = std::make_unique<InputManager>();

	auto mode = std::make_unique<ModeStart>(*this);
	//auto mode = std::make_unique<ModeGame>(*this);
	_modeServer->Add(std::move(mode));
}

void Game::Input() {
	_inputManager->InputUpdate();
	if (_inputManager->CheckInput("CHANGE", 'r', 0)|| _inputManager->CheckInput("CHANGE", 'r', 1)) {
		_inputManager->ChangeControllerNo();
	}
	if (_inputManager->CheckInput("DEBUG", 'r', 0) || _inputManager->CheckInput("DEBUG", 'r', 1)) {
		_debug = !_debug;
	}
}
void Game::Update() {
	++_frameCount;
	_modeServer->Update();
}

void Game::Render() {
	_modeServer ->Render();
}

void Game::Debug(){
	if (_debug) {
		_modeServer->Debug();
	}
	//_inputManager->Render();
}