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
#include "ModeStartUp2.h"

Game::Game()
	:_frameCount{ 0 }
	, _progress{ Progress::StartMenu }
	, _network{ nullptr }
	, _online{-1}
{
	_modeServer = std::make_unique<ModeServer>(*this);
	_inputManager = std::make_unique<InputManager>();
	//PlayStartUp1();
	PlayStartMenu();
	//PlayStage2Clear();
	_font22 = LoadFontDataToHandle("resource/Font/ロンドBスクエア.dft", 1);
	_font26 = LoadFontDataToHandle("resource/Font/ロンドBスクエア26.dft", 1);
}

void Game::Input() {
	_inputManager->InputUpdate();
	if (_network != nullptr) {
		_network->Update();
	}
#ifdef _DEBUG
	if (_inputManager->CheckInput("CHANGE", 'r', 0) || _inputManager->CheckInput("CHANGE", 'r', 1)) {
		_inputManager->ChangeControllerNo();
	}
	if (_inputManager->CheckInput("DEBUG", 'r', 0) || _inputManager->CheckInput("DEBUG", 'r', 1)) {
		_debug = !_debug;
	}

#endif // _DEBUG


}
void Game::Update() {
	++_frameCount;
	_modeServer->Update();

#ifdef _DEBUG
	if (_inputManager->CheckInput("DEBUG", 'h', 0) && _inputManager->CheckInput("PAUSE", 't', 0) ||
		_inputManager->CheckInput("DEBUG", 'h', 1) && _inputManager->CheckInput("PAUSE", 't', 1))
	{
		PlayStartMenu();
	}

#endif // DEBUG
}

void Game::Render() {
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	_modeServer->Render();
}

void Game::Debug() {
	if (_debug) {

		_modeServer->Debug();
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", GetFPS());
		DrawFormatString(0, 12, GetColor(255, 255, 255), "%d", GetASyncLoadNum());
		if (_network != nullptr) {
			_network->Debug();
		}

#ifdef _DEBUG
		_inputManager->Render();
#endif 
	}
}

void Game::RestartMode() {
	SetDrawArea(0, 0, screen_W, screen_H);
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

void Game::NextMode() {
	SetDrawArea(0, 0, screen_W, screen_H);
	switch (_progress)
	{
	case Game::Progress::StartUp1:
		PlayStartUp2();
		break;
	case Game::Progress::StartUp2:
		PlayStartUp3();
		break;
	case Game::Progress::StartUp3:
		PlayStartMenu();
		break;
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
	case Game::Progress::Credit:
		PlayStartMenuSkipMovie();
		break;
	}
}

void Game::PlayStartUp1() {
	SoundServer::StopALLSound();
	_progress = Progress::StartUp1;
	StopSoundFile();
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/startup1.mp4", 0, 0, false)));
}

void Game::PlayStartUp2() {
	_modeServer->Clear();
	SoundServer::StopALLSound();
	_progress = Progress::StartUp2;
	StopSoundFile();
	_modeServer->Add(std::move(std::make_unique<ModeStartUp2>(*this)));
}

void Game::PlayStartUp3() {
	SoundServer::StopALLSound();
	_progress = Progress::StartUp3;
	StopSoundFile();
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/startup3.mp4", 0, 0, false)));
}


void Game::PlayIntro() {

}

void Game::PlayStartMenu() {
	SoundServer::StopALLSound();
	_progress = Progress::StartMenu;
	StopSoundFile();
	_modeServer->Clear();
	_modeServer->Add(std::move(std::make_unique<ModeStart>(*this, 0)));
}

void Game::PlayStartMenuSkipMovie() {
	SoundServer::StopALLSound();
	_progress = Progress::StartMenu;
	StopSoundFile();
	_modeServer->Clear();
	_modeServer->Add(std::move(std::make_unique<ModeStart>(*this, 125000)));
}

void Game::PlayStage1() {
	SetUseASyncLoadFlag(true);
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage1;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 6;
	pattern.body = 2;
	pattern.foot = 2;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage1.json", pattern, "resource/BGM/Stage1.mp3")));
	SetUseASyncLoadFlag(false);
}

void Game::PlayStage2() {
	SetUseASyncLoadFlag(true);
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage2;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 9;
	pattern.body = 5;
	pattern.foot = 5;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage2.json", pattern, "resource/BGM/Stage2.mp3")));
	SetUseASyncLoadFlag(false);
}

void Game::PlayStage3() {
	SoundServer::StopALLSound();
	_modeServer->Clear();
	SetUseASyncLoadFlag(false);
	LoadResources::LoadBossCGs();
	SetUseASyncLoadFlag(true);
	_progress = Progress::Stage3;
	EnemyGenerator::EnemyPattern pattern;
	pattern.head = 9;
	pattern.body = 5;
	pattern.foot = 5;
	_modeServer->Add(std::move(std::make_unique<ModeGame>(*this, "Stage3.json", pattern, "resource/BGM/title.mp3")));
	SetUseASyncLoadFlag(false);
}

void Game::PlayStage1Clear() {
	SetUseASyncLoadFlag(true);
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage1Clear;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/stage1end.mp4", 0, 137000, true)));
	SetUseASyncLoadFlag(false);
}

void Game::PlayStage2Clear() {
	SetUseASyncLoadFlag(true);
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage2Clear;
	auto movie = std::make_unique<ModeMovie>(*this, "resource/Movie/stage2end.mp4", 0, 86500, true);
	movie->SetBGM("resource/BGM/title.mp3", 91000);
	_modeServer->Add(std::move(movie));
	LoadResources::LoadBossCGs();
	SetUseASyncLoadFlag(false);
}

void Game::PlayStage3Clear() {
	SetUseASyncLoadFlag(true);
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Stage3Clear;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/stage3end.mp4", 0, 0, true)));
	SetUseASyncLoadFlag(false);
}

void Game::GameOver() {
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();

	auto mode = std::make_unique<ModeGameOver>(*this);
	_modeServer->Add(std::move(mode));
}

void Game::PlayCredit() {
	SoundServer::StopALLSound();
	StopSoundFile();
	_modeServer->Clear();
	_progress = Progress::Credit;
	_modeServer->Add(std::move(std::make_unique<ModeMovie>(*this, "resource/Movie/stage3end.mp4", 152000, 222000, true)));
}

void Game::StartNetwork() {
	if (_network == nullptr) {
		_network.reset(new Network(*this));
	}
}
