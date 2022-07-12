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

	void Update();
	void Render();
	void Debug();


	inline  auto& GetMapChips() { return _mapChips; }
	inline auto& GetSplitWindow() { return _splitWindow; }

private:
	bool _stopObjectProccess;

	std::unique_ptr<MapChips>_mapChips;
	std::vector<std::unique_ptr<SplitWindow>>_splitWindow;
	std::unique_ptr <ActorServer> _actorServer;

	std::shared_ptr<InputManager> _inputManager;
};
