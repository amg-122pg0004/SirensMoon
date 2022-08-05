/*****************************************************************//**
 * \file   ModeGame.cpp
 * \brief  ゲーム中に使用するモードです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "ModeGame.h"
#include "Enemy.h"
#include "HPItem.h"
#include "BulletItem.h"
#include "ServerMachine.h"
#include "SoundServer.h"
#include "EnemyGenerator.h"
#include "ModeMovie.h"
#include "FloorLamp.h"
#include "Tereporter.h"

ModeGame::ModeGame(Game& game) :ModeBase{ game }, _stopActorUpdate{false},_blindFlag{false}
{

	_inputManager=_game.GetInputManager();

	_mapChips = std::make_unique<MapChips>(_game,*this);

	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, 0, 0, 0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, screen_W / 2, 0, 1));

	EnemyGenerator::EnemyPattern pattern;
	pattern.body = 3;
	pattern.head = 3;
	pattern.foot = 3;

	auto enemygen = std::make_unique<EnemyGenerator>(pattern);

	auto serverdata = _mapChips->GetServerData();
	for (auto&& data : serverdata) {
		auto pattern =enemygen->GetEnemyVIPPattern();
		auto server = std::make_unique<ServerMachine>(_game, *this, data,pattern);
		_actorServer.Add(std::move(server));
	}

	auto enemydata=_mapChips->GetEnemyData();
	for (auto&& data : enemydata) {
		auto pattern = enemygen->GetEnemyPattern();
		auto enemy = std::make_unique<Enemy>(_game, *this, data,pattern);
		_actorServer.Add(std::move(enemy));
	}

	auto hp_pos = _mapChips->GetHPItemData();
	for (int i=0; i < hp_pos.size();++i) {
		auto hp = std::make_unique<HPItem>(_game, *this, hp_pos[i]);
		_actorServer.Add(std::move(hp));
	}

	auto bullet_pos = _mapChips->GetBulletData();
	for (int i=0; i < bullet_pos.size(); ++i) {
		auto bullet = std::make_unique<BulletItem>(_game, *this, bullet_pos[i]);
		_actorServer.Add(std::move(bullet));
	}

	auto light_pos = _mapChips->GetLightData();
	for (int i = 0; i < light_pos.size(); ++i) {
		auto lamp = std::make_unique<FloorLamp>(_game, *this, light_pos[i]);
		_actorServer.Add(std::move(lamp));
	}

	auto tereportIn_pos = _mapChips->GetTereporterInData();
	for (int i = 0; i < tereportIn_pos.size(); ++i) {
		auto tereportin = std::make_unique<TereporterIn>(_game, *this, tereportIn_pos[i]);
		_actorServer.Add(std::move(tereportin));
	}
	
	auto data = _mapChips->GetTereporterOutData();
	for (auto&& pair:data) {
		auto tereportout = std::make_unique<TereporterOut>(_game, *this, pair.second.first);
		_actorServer.Add(std::move(tereportout));
	}
	

	LoadResource();
}

void ModeGame::LoadResource() {
	SoundServer::LoadSound("PlayerWalk", "resource/Sounds/Player/se_sk2206.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerWalk"));
	SoundServer::LoadSound("PlayerRun", "resource/Sounds/Player/se_sk2207.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerRun"));
	SoundServer::LoadSound("PlayerAim", "resource/Sounds/Player/se_sk2054.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerAim"));
	SoundServer::LoadSound("PlayerCharge", "resource/Sounds/Player/se_sk2153.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerCharge"));
	SoundServer::LoadSound("PlayerShoot", "resource/Sounds/Player/se_sk2177.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerShoot"));
	SoundServer::LoadSound("PlayerChargeMAX", "resource/Sounds/Player/se_sk2224.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerChargeMAX"));
	SoundServer::LoadSound("BulletToWall", "resource/Sounds/Player/se_sk2026.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("BulletToWall"));
	SoundServer::LoadSound("BulletToEnemy", "resource/Sounds/Player/se_sk2020.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("BulletToEnemy"));
	SoundServer::LoadSound("PlayerOpenMap", "resource/Sounds/Player/se_sk2050.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerOpenMap"));
}

void ModeGame::Update() {
	if (_inputManager->CheckInput("BLIND", 't', 0) || _inputManager->CheckInput("BLIND", 't', 1)) {
		_blindFlag = !_blindFlag;
	}
	/*UIの更新*/
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Update();
	}
	/*Actorの更新*/
	if (_stopActorUpdate!=1) {
		_actorServer.Update();
	}

}

void ModeGame::Render() {
	ClearDrawScreen();

	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Render();
	}
	//_inputManager->Render();
}

void ModeGame::Debug() {
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Debug();
	}
}

void ModeGame::StageClearCheck(){
	++_enemyVIPDeadCount;
	if (_enemyVIPDeadCount >= _mapChips->GetServerData().size()) {
		auto mode = std::make_unique<ModeMovie>(_game, "resource/Movie/rocket.mp4");
		_game.GetModeServer()->Add(std::move(mode));
	}
}
