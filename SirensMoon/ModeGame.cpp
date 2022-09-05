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
#include "BreakableObject.h"
#include "DegitalLetter.h"
#include "BossGimmickController.h"
#include "SwitchArea.h"
#include "ScreenPump.h"

ModeGame::ModeGame(Game& game, std::string filename, EnemyGenerator::EnemyPattern pattern,std::string bgm) 
	:ModeBase{ game }, _stopActorUpdate{false} ,_bgm{bgm},_clearDelay{240},_clear{false}
{
	_inputManager=_game.GetInputManager();

	SetUseASyncLoadFlag(true);
	_renderPriority = 0;

	PlaySoundFile(bgm.c_str(), DX_PLAYTYPE_LOOP);
	_mapChips = std::make_unique<MapChips>(_game,*this,filename);

	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, 0, 0, 0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, screen_W-splitscreen_W, 0, 1));

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



	auto doordata = _mapChips->GetDoorData();
	for (auto adoor : doordata) {
		auto door = std::make_unique<Door>(_game, *this, adoor);
		_actorServer.Add(std::move(door));
	}

	auto tntdata = _mapChips->GetTNTData();
	for (auto atnt : tntdata) {
		auto tnt = std::make_unique<TNT>(_game, *this, atnt);
		_actorServer.Add(std::move(tnt));
	}

	auto minedata = _mapChips->GetMineData();
	for (auto amine : minedata) {
		auto mine = std::make_unique<Mine>(_game, *this, amine);
		_actorServer.Add(std::move(mine));
	}
	auto v_screen = _mapChips->GetScreenPumpData();
	for (auto a_screen : v_screen) {
		auto screen = std::make_unique<ScreenPump>(_game, *this, a_screen);
		_actorServer.Add(std::move(screen));
	}


	auto stickydata = _mapChips->GetStikyBombData();
	for (auto astick : stickydata) {
		auto stick = std::make_unique<StickyBomb>(_game, *this, astick);
		_actorServer.Add(std::move(stick));
	}
	
	auto breakabledata = _mapChips->GetBreakableObjectData();
	for (auto abreakable : breakabledata) {
		auto breakable = std::make_unique<BreakableObject>(_game, *this, abreakable);
		_actorServer.Add(std::move(breakable));
	}

	auto switchareadata = _mapChips->GetSwitchAreaData();
	for (auto aswitcharea : switchareadata) {
		auto switcharea_obj = std::make_unique<SwitchArea>(_game, *this, aswitcharea);
		_actorServer.Add(std::move(switcharea_obj));
	}

	auto switchdata = _mapChips->GetSwitchData();
	for (auto aswitch : switchdata) {
		auto switch_obj = std::make_unique<Switch>(_game, *this, aswitch);
		_actorServer.Add(std::move(switch_obj));
	}

	auto degitaldata = _mapChips->GetDegitalLetterData();
	for (auto adedital : degitaldata) {
		auto degital = std::make_unique<DegitalLetter>(_game, *this, adedital);
		_actorServer.Add(std::move(degital));
	}

	auto bossspawndata = _mapChips->GetBossGimmickControllerDataList();
	for (auto aspawn : bossspawndata) {
		auto bosscon = std::make_unique<BossGimmickController>(_game, *this, aspawn);
		_actorServer.Add(std::move(bosscon));
	}


	LoadResources::LoadSE();
	LoadResources::LoadEffects();
	LoadResources::LoadMovie("resource/Movie/gameover.mp4");
}

ModeGame::~ModeGame() {
	_splitWindow.clear();
	_inputManager.reset();
	_mapChips.reset();
}

void ModeGame::Update() {
	ModeBase::Update();
	/*UIの更新*/
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Update();
	}
	/*Actorの更新*/
	if (_stopActorUpdate==false) {
		_actorServer.Update();
	}
	if (_clear) {
		--_clearDelay;
		if (_clearDelay < 0) {
			ModeBase::NextMode();
		}
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
	_stopActorUpdate = true;
	++_enemyVIPDeadCount;
	if (_enemyVIPDeadCount >= _mapChips->GetServerData().size()) {
		StopSoundFile();
		_stopActorUpdate = true;
		TargetKillEvent();
		_clear = true;
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

void ModeGame::TargetKillEvent() {
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->TargetKillEvent();
	}
}

void ModeGame::SetPauseGame(bool flag){
	if (!_makedNextMode) {
		_stopActorUpdate = flag;
	}
}
void ModeGame::PlayBGM(){
	StopSoundFile();
	PlaySoundFile(_bgm.c_str(), DX_PLAYTYPE_LOOP);
}
