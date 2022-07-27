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

ModeGame::ModeGame(Game& game) :ModeBase{ game }, _stopActorUpdate{false}
{

	_inputManager=_game.GetInputManager();

	_mapChips = std::make_unique<MapChips>(_game,*this);

	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, 0, 0, 0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, screen_W / 2, 0, 1));

	Vector2 pos = { 300,600 };
	auto server = std::make_unique<ServerMachine>(_game, *this, pos, 4);
	_wantedEnemys.push_back(server->GetGeneratedEnemy());
	_actorServer.Add(std::move(server));


	auto enemydata=_mapChips->GetEnemyData();
	for (auto&& data : enemydata) {
		if (data.ID != 1) {
			auto enemy = std::make_unique<Enemy>(_game, *this, data);
			_actorServer.Add(std::move(enemy));
		}
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