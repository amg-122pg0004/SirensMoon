/*****************************************************************//**
 * \file   ModeGame.cpp
 * \brief  ゲーム中に使用するモードです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "ModeGame.h"
#include "EnemyA.h"
#include "EnemyB.h"
#include "HPItem.h"
#include "BulletItem.h"
#include "ServerMachine.h"
#include "SoundServer.h"
#include "ModeMovie.h"
#include "FloorLamp.h"
#include "teleporter.h"
#include "Switch.h"
#include "Door.h"
#include "TNT.h"
#include "Mine.h"
#include "ModeGameOver.h"
#include "StickeyBomb.h"

ModeGame::ModeGame(Game& game) :ModeBase{ game }, _stopActorUpdate{false},_blindFlag{false},_makedNextMode{false}
{

	_inputManager=_game.GetInputManager();

	_mapChips = std::make_unique<MapChips>(_game,*this);

	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, 0, 0, 0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, screen_W-splitscreen_W, 0, 1));

	EnemyGenerator::EnemyPattern pattern;
	pattern.body = 2;
	pattern.head = 2;
	pattern.foot = 2;
	/*各部2種で敵ランダム生成*/
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
		auto enemy = std::make_unique<EnemyA>(_game, *this, data,pattern);
		_actorServer.Add(std::move(enemy));
	}

	auto enemybdata = _mapChips->GetEnemyBData();
	for (auto&& data : enemybdata) {
		auto pattern = enemygen->GetEnemyPattern();
		auto enemy = std::make_unique<EnemyB>(_game, *this, data, pattern);
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
		auto lamp = std::make_unique<FloorLamp>(_game, *this, light_pos[i].first, light_pos[i].second);
		_actorServer.Add(std::move(lamp));
	}
	
	auto teleportIn_pos = _mapChips->GetteleporterInData();
	for (int i = 0; i < teleportIn_pos.size(); ++i) {
		auto teleportin = std::make_unique<teleporterIn>(_game, *this,-1, teleportIn_pos[i]);
		_actorServer.Add(std::move(teleportin));
	}
	
	auto data = _mapChips->GetteleporterOutData();
	for (auto&& pair:data) {
		auto teleportout = std::make_unique<teleporterOut>(_game, *this,-1, pair.second.first);
		_actorServer.Add(std::move(teleportout));
	}

	auto switchdata = _mapChips->GetSwitchData();
	for (auto aswitch  : switchdata) {
		auto switch_obj = std::make_unique<Switch>(_game, *this,aswitch);
		_actorServer.Add(std::move(switch_obj));
	}

	auto doordata = _mapChips->GetDoorData();
	for (auto adoor : doordata) {
		auto door = std::make_unique<Door>(_game, *this, adoor.first,adoor.second);
		_actorServer.Add(std::move(door));
	}

	auto tntdata = _mapChips->GetTNTData();
	for (auto atnt : tntdata) {
		auto tnt = std::make_unique<TNT>(_game, *this, atnt.first, atnt.second);
		_actorServer.Add(std::move(tnt));
	}

	auto minedata = _mapChips->GetMineData();
	for (auto amine : minedata) {
		auto mine = std::make_unique<Mine>(_game, *this, amine);
		_actorServer.Add(std::move(mine));
	}

	auto stickydata = _mapChips->GetStikyBombData();
	for (auto astick : stickydata) {
		auto stick = std::make_unique<StickyBomb>(_game, *this, astick);
		_actorServer.Add(std::move(stick));
	}

	std::vector<int> cg;
	cg.resize(120);
	ImageServer::LoadDivGraph("resource/Effect/boom.png", 120, 8, 15, 512, 512, cg.data());
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
	SoundServer::LoadSound("Explosion", "resource/Sounds/Gimmick/se_sk2063.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerOpenMap"));
	SoundServer::LoadSound("DamageToPlayer", "resource/Sounds/Enemy/se_sk2077.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("DamageToPlayer"));
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
	if (_stopActorUpdate==false) {
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
	if (_makedNextMode == false) {
		_makedNextMode = true;
		if (_enemyVIPDeadCount >= _mapChips->GetServerData().size()) {
			_stopActorUpdate = true;

			auto mode = std::make_unique<ModeMovie>(_game, "resource/Movie/rocket.mp4");
			_game.GetModeServer()->Add(std::move(mode));
		}
	}

}

void ModeGame::GameOver(){
	_stopActorUpdate = true;
	if (_makedNextMode == false) {
		_makedNextMode = true;
		auto mode = std::make_unique<ModeGameOver>(_game);
		_game.GetModeServer()->Add(std::move(mode));
	}
}

void ModeGame::DamageEvent(){
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->DamageEvent();
	}
}

void ModeGame::SetPauseGame(bool flag){
	if (!_makedNextMode) {
		_stopActorUpdate = flag;
	}
}
