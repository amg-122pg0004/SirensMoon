#include "ModeGameOver.h"
#include "Game.h"
#include "ModeGame.h"


ModeGameOver::ModeGameOver(Game& game):ModeBase(game), _restart{false},_delay{60}
{
	_inputManager = _game.GetInputManager();
	_renderPriority = 2;

	_movieHandle = ImageServer::LoadGraph("resource/Movie/gameover.mp4");

}

void ModeGameOver::Update(){
	--_delay;
	if (_delay == 0) {
		PlayMovieToGraph(_movieHandle);
	}
	if (_delay <= 0) {
		if (_inputManager->CheckInput("ACCESS", 't', 0) || _inputManager->CheckInput("ACCESS", 't', 1)) {
			RestartGame();
			_restart = true;
		}
		if (_restart == false && GetMovieStateToGraph(_movieHandle) != 1) {
			RestartGame();
		}
	}
}

void ModeGameOver::Render() {
	SetDrawArea(0, 0, screen_W, screen_H);
	if (_delay <= 0) {
		DrawGraph(0, 0, _movieHandle, 0);
		DrawGraph(screen_W - splitscreen_W, 0, _movieHandle, 0);
	}
}

void ModeGameOver::RestartGame(){
	PauseMovieToGraph(_movieHandle);
	SeekMovieToGraph(_movieHandle, 0);
	_game.GetModeServer()->Clear();

	auto mode = std::make_unique<ModeGame>(_game);

	_game.GetModeServer()->Add(std::move(mode));



}
