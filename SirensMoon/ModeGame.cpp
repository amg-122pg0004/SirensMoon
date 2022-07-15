#include "ModeGame.h"
#include "Enemy.h"

ModeGame::ModeGame(Game& game) :ModeBase{ game }
{

	_inputManager=_game.GetInputManager();

	_stopObjectProccess = false;

	_mapChips = std::make_unique<MapChips>(_game,*this);

	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, 0, 0, 0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, screen_W / 2, 0, 1));

	auto enemydata=_mapChips->GetEnemyData();
	for (auto&& data : enemydata) {
		auto enemy =std::make_unique<Enemy>(_game, *this, data);
		_actorServer.Add(std::move(enemy));
	}
}

void ModeGame::Update() {
	_actorServer.Update();
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