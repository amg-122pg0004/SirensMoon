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
	PlayStage2Clear();
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
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", GetFPS());
	}
}


void Game::RestartMode() {
	SetDrawArea(0,0,screen_W,screen_H);
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
	SetDrawArea(0, 0, screen_W, screen_H);
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
	case Game::Progress::Stage3:
		PlayStage3Clear();
		break;
	case Game::Progress::Stage3Clear:
		PlayStartMenu();
		break;
	}
}

void Game::PlayStartMenu() {
	SoundServer::StopALLSound();
	_progress = Progress::StartMenu;
	StopSoundFile();
	_modeServer->Clear();
	_modeServer->Add(std::move(std::make_unique<ModeStart>(*this)));
}

void Game::PlayStage1() {
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage1;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 6;
	pattern.body = 2;
	pattern.foot = 2;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage1.json", pattern, "resource/BGM/Stage1.wav")));
}

void Game::PlayStage2() {
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage2;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 9;
	pattern.body = 5;
	pattern.foot = 5;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage2.json", pattern, "resource/BGM/Stage2.wav")));
}

void Game::PlayStage3() {
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	SetUseASyncLoadFlag(false);
	LoadResources::LoadBossCGs();
	SetUseASyncLoadFlag(true);
	_progress = Progress::Stage3;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 9;
	pattern.body = 5;
	pattern.foot = 5;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage3.json", pattern, "resource/BGM/Stage3.wav")));
}

void Game::PlayStage1Clear() {
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage1Clear;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/stage1end.mp4")));
}

void Game::PlayStage2Clear() {
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage2Clear;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/stage2end.mp4")));
	SetUseASyncLoadFlag(true);
	LoadResources::LoadBossCGs();
}

void Game::PlayStage3Clear() {
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage3Clear;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/stage2end.mp4")));
}

void Game::GameOver(){
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();

	auto mode = std::make_unique<ModeGameOver>(*this);
	_modeServer->Add(std::move(mode));
}