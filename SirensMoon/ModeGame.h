/*****************************************************************//**
 * \file   ModeGame.h
 * \brief  �Q�[�����Ɏg�p���郂�[�h�ł��B
 * 
 * \author �y�������Y
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

	/*���݂��̃v���C���[�����F�ł��Ȃ��Ȃ�t���O*/
	bool _blindFlag;

	bool _makedNextMode;
};