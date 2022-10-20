#include "ModeGameOver.h"
#include "Game.h"
#include "ModeGame.h"


ModeGameOver::ModeGameOver(Game& game):ModeBase(game), _restart{false},_delay{60}
{
	_inputManager = _game.GetInputManager();
	_renderPriority = 2;
	SoundServer::StopALLSound();
	StopSoundFile();
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
		DrawExtendGraph(0, 0,splitscreen_W,screen_H, _movieHandle, 0);
		DrawExtendGraph(screen_W - splitscreen_W, 0, screen_W, screen_H, _movieHandle, 0);
	}
	ModeBase::RenderOnlineBlind();
}

void ModeGameOver::RestartGame(){
	PauseMovieToGraph(_movieHandle);
	SeekMovieToGraph(_movieHandle, 0);
	_game.RestartMode();
}
