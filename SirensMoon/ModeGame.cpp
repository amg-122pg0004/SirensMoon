#include "ModeGame.h"

ModeGame::ModeGame(Game& game) 
	:ModeGame{ game }
{
	_actorServer = std::make_unique<ActorServer>();

	_inputManager=_game.GetInputManager();

	_stopObjectProccess = false;

	_mapChips = std::make_unique<MapChips>(*this);
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(*this, 0, 0, 0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(*this, screen_W / 2, 0, 1));
}

void ModeGame::Update() {
	_actorServer->Update();
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Update();
	}
}

void ModeGame::Render() {
	ClearDrawScreen();

	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Render();
	}
	_inputManager->Render();
}

void ModeGame::Debug() {
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Debug();
	}
}
