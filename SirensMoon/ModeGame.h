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
class Game;

class ModeGame :public ModeBase {

public:
	ModeGame(Game& game);

	void Update()override;
	void Render()override;
	void Debug()override;

	void LoadResource();


	inline  auto& GetMapChips() { return _mapChips; }
	inline auto& GetSplitWindow() { return _splitWindow; }
	bool GetBlindFlag() { return _blindFlag; }

	void SetPauseGame(bool flag);
	void StageClearCheck();
	void GameOver();
	void DamageEvent();
	
private:
	bool _stopActorUpdate;

	std::unique_ptr<MapChips>_mapChips;
	std::vector<std::unique_ptr<SplitWindow>>_splitWindow;

	std::shared_ptr<InputManager> _inputManager;

	int _enemyVIPDeadCount;

	/*お互いのプレイヤーを視認できなくなるフラグ*/
	bool _blindFlag;

	bool _makedNextMode;
};