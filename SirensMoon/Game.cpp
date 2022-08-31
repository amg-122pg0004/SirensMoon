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
#include "EnemyGenerator.h"

#include "ModeGameOver.h"
#include "ModeMovie.h"

Game::Game() :_frameCount{0},_progress{Progress::StartMenu}
{
	_modeServer = std::make_unique<ModeServer>(*this);
	_inputManager = std::make_unique<InputManager>();

	//PlayStartMenu();
	PlayStage1();
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


void Game::RestartMode() {
	switch (_progress)
	{
	case Game::Progress::StartMenu:
		PlayStartMenu();
		break;

	case Game::Progress::Stage1:
		PlayStage1();
		break;

	case Game::Progress::Stage2:
		PlayStage2();
		break;

	case Game::Progress::Stage3:
		PlayStage3();
		break;
	}
}

void Game::NextMode(){
	StopSoundFile();
	switch (_progress)
	{
	case Game::Progress::StartMenu:
		PlayStage1();
		break;
	case Game::Progress::Stage1:
		PlayStage1Clear();
		break;
	case Game::Progress::Stage1Clear:
		PlayStage2();
		break;
	case Game::Progress::Stage2:
		PlayStage2Clear();
		break;
	case Game::Progress::Stage2Clear:
		PlayStage3();
		break;
	case Game::Progress::Stage3 :
		PlayStage3Clear();
		break;
	case Game::Progress::Stage3Clear:
		PlayStartMenu();
		break;
	}
}

void Game::PlayStartMenu() {
	_modeServer->Clear();
	_modeServer->Add(std::move(std::make_unique<ModeStart>(*this)));
}

void Game::PlayStage1() {
	_modeServer->Clear();
	_progress = Progress::Stage1;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 6;
	pattern.body = 2;
	pattern.foot = 2;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage1.json", pattern)));
}

void Game::PlayStage2() {
	_modeServer->Clear();
	_progress = Progress::Stage2;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 9;
	pattern.body = 5;
	pattern.foot = 5;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage2.json", pattern)));
}

void Game::PlayStage3() {
	_modeServer->Clear();
	_progress = Progress::Stage3;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 9;
	pattern.body = 5;
	pattern.foot = 5;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage3.json", pattern)));
}

void Game::PlayStage1Clear() {
	_progress = Progress::Stage1Clear;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/rocket.mp4")));
}

void Game::PlayStage2Clear() {
	_progress = Progress::Stage2Clear;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/rocket.mp4")));
}

void Game::PlayStage3Clear() {
	_progress = Progress::Stage3Clear;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/rocket.mp4")));
}

void Game::GameOver(){
	_modeServer->Clear();

	auto mode = std::make_unique<ModeGameOver>(*this);
	_modeServer->Add(std::move(mode));
}