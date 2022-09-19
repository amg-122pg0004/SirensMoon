#include "ModeStartUp2.h"
#include "Game.h"
#include "ModeGame.h"

ModeStartUp2::ModeStartUp2(Game& game) :ModeBase(game)
	, _pushPlayerA{false}, _pushPlayerB{false}
{
	_inputManager = _game.GetInputManager();

	LoadResources::LoadSE1();
	_movieHandle = ImageServer::LoadGraph("resource/Movie/startup2.mp4");
	_cg_red = ImageServer::LoadGraph("resource/UI/StartUp/RedSun.png");
	_cg_blue = ImageServer::LoadGraph("resource/UI/StartUp/BlueSun.png");
	PlayMovieToGraph(_movieHandle);
}

void ModeStartUp2::Update() {
	ModeBase::Update();
	if(_inputManager->CheckInput("ACCESS", 't', 0)) {
		_pushPlayerA = true;
	}
	if (_inputManager->CheckInput("ACCESS", 't', 1)) {
		_pushPlayerB = true;
	}
	if (_pushPlayerA && _pushPlayerB) {
		ModeBase::NextMode();
	}
	if (GetMovieStateToGraph(_movieHandle) == 0) {
		SeekMovieToGraph(_movieHandle,0);
		PlayMovieToGraph(_movieHandle);
	}
}

void ModeStartUp2::Render() {
	DrawExtendGraph(0, 0, screen_W, screen_H, _movieHandle, 0);
	if (_pushPlayerA) {
		DrawGraph(180, 400, _cg_red, 1);
	}
	if (_pushPlayerB) {
		DrawGraph(screen_W- 180 -180, 400, _cg_blue, 1);
	}
}

void ModeStartUp2::Debug() {

}