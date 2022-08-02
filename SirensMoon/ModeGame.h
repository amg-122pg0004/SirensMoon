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

	void SetPauseGame(bool flag) { _stopActorUpdate = flag; }
	void StageClearCheck();
	
	
private:
	bool _stopActorUpdate;

	int _lightUp;

	std::unique_ptr<MapChips>_mapChips;
	std::vector<std::unique_ptr<SplitWindow>>_splitWindow;

	std::shared_ptr<InputManager> _inputManager;

	int _enemyVIPDeadCount;
};