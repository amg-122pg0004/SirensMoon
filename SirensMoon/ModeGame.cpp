#include "ModeGame.h"
#include "Enemy.h"
#include "HPItem.h"
#include "BulletItem.h"

ModeGame::ModeGame(Game& game) :ModeBase{ game }, _stopActorUpdate{false}
{

	_inputManager=_game.GetInputManager();

	_mapChips = std::make_unique<MapChips>(_game,*this);

	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, 0, 0, 0));
	_splitWindow.emplace_back(std::make_unique<SplitWindow>(_game,*this, screen_W / 2, 0, 1));

	auto enemydata=_mapChips->GetEnemyData();
	for (auto&& data : enemydata) {
		auto enemy =std::make_unique<Enemy>(_game, *this, data);
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
}

void ModeGame::Update() {
	/*UIの更新*/
	for (auto&& splitwindows : _splitWindow) {
		splitwindows->Update();
	}
	/*Actorの更新*/
	if (_stopActorUpdate!=1) {
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