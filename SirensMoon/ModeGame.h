/*****************************************************************//**
 * \file   ModeGame.h
 * \brief  ゲーム中に使用するモードです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "ModeBase.h"
#include "SplitWindow.h"
#include "ActorServer.h"
#include "MapChip.h"
#include "Camera.h"
#include "LoadResources.h"
#include "EnemyGenerator.h"

class Game;

class ModeGame :public ModeBase {

public:
	ModeGame(Game& game,std::string filename, EnemyGenerator::EnemyPattern pattern,std::string bgm);
	~ModeGame();

	void Update()override;
	void Render()override;
	void Debug()override;

	inline  auto& GetMapChips() { return _mapChips; }
	inline auto& GetSplitWindow() { return _splitWindow; }

	void SetPauseGame(bool flag);
	void StageClearCheck();
	void GameClear();
	void GameOver();
	void DamageEvent();
	void TargetKillEvent();
	void PlayBGM();
	
private:
	bool _stopActorUpdate;

	std::unique_ptr<MapChips>_mapChips;
	std::vector<std::unique_ptr<SplitWindow>>_splitWindow;
	std::shared_ptr<InputManager> _inputManager;
	std::string _bgm;
	int _enemyVIPDeadCount;
};