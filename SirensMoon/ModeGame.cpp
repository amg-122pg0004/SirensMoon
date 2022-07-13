#include "ModeGame.h"
#include "Enemy.h"

ModeGame::ModeGame(Game& game) :ModeBase{ game }
{

	_inputManager=_game.GetInputManager();

	_stopObjectProccess = false;

	_mapChips = std::make_unique<MapChips>(_game,*this);

	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, 0, 0, 0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, screen_W / 2, 0, 1));

	Vector2 pos = { 0, 0 };
	auto enemy = std::make_unique<Enemy>(_game,*this,pos);
	_actorServer.Add(std::move(enemy));

	Vector2 pos2 = { 1050, 1050 };
	auto enemy2 = std::make_unique<Enemy>(_game, *this, pos2);
	_actorServer.Add(std::move(enemy2));

	Vector2 pos3 = { 2050, 2150 };
	auto enemy3 = std::make_unique<Enemy>(_game, *this, pos3);
	_actorServer.Add(std::move(enemy3));
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
