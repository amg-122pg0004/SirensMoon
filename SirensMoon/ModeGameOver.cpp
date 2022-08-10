#include "ModeGameOver.h"
#include "Game.h"
#include "GameOverUI.h"
#include "ModeGame.h"


ModeGameOver::ModeGameOver(Game& game):ModeBase(game)
{
	_inputManager = _game.GetInputManager();

	Vector2 pos = { 0,0 };
	Vector2 size = { 930,1080 };
	auto ui = std::make_unique<GameOverUI>(game,*this, pos, size);
	_ui.emplace_back(std::move(ui));
}

void ModeGameOver::Update(){
	for (auto&& ui : _ui) {
		ui->Update();
	}
}

void ModeGameOver::Render() {
	for (auto&& ui : _ui) {
		ui->Render();
	}
}

void ModeGameOver::RestartGame(){
	_game.GetModeServer()->Clear();

	auto mode = std::make_unique<ModeGame>(_game);
	_game.GetModeServer()->Add(std::move(mode));
}
