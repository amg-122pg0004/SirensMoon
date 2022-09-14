/*****************************************************************//**
 * \file   ModeMovie.cpp
 * \brief  �Q�[�����Ƀ��[�r�[�������V�[���Ŏg�p���郂�[�h�ł�
 * 
 * \author �y�������Y
 * \date   August 2022
 *********************************************************************/
#include "ModeMovie.h"
#include "ImageServer.h"
#include "Game.h"
#include "LoadResources.h"

ModeMovie::ModeMovie(Game& game,std::string path, int skipFrame)
	:ModeBase{game} ,_sizeX{0},_sizeY{0}, _movieSkipFrame{ skipFrame }
{
	_renderPriority = 10;
	_movieHandle=ImageServer::LoadGraph(path);
	SeekMovieToGraph(_movieHandle,0);
	PlayMovieToGraph(_movieHandle);

	GetGraphSize(_movieHandle, &_sizeX, &_sizeY);
	_makedNextMode = false;

	SetUseASyncLoadFlag(true);
	LoadResources::LoadSE();
	LoadResources::LoadEffects();
}

void ModeMovie::Update() {
	ModeBase::Update();
	/*PAUSE�{�^���ŃX�L�b�v*/

	if (_game.GetInputManager()->CheckInput("PAUSE", 't', 0) || _game.GetInputManager()->CheckInput("PAUSE", 't', 1)) {
		if (TellMovieToGraph(_movieHandle) < _movieSkipFrame) {
			auto tesu =TellMovieToGraph(_movieHandle);
			if (GetASyncLoadNum() == 0) {
				SeekMovieToGraph(_movieHandle, _movieSkipFrame);
			}
		}
	}
	/*�Đ����I�������X�L�b�v*/
	if (GetMovieStateToGraph(_movieHandle)==0) {
		PauseMovieToGraph(_movieHandle);
		ModeBase::NextMode();
	}
}

void ModeMovie::Render() {
	SetDrawArea(0, 0, screen_W, screen_H);
	DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
	auto scale = static_cast<double>(_sizeY) / static_cast<double>(_sizeX);
	DrawGraph(0,0,_movieHandle, 0);
	DrawGraph(screen_W - splitscreen_W,0, _movieHandle, 0);
}

void ModeMovie::Debug() {

}
