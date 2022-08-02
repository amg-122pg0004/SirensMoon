/*****************************************************************//**
 * \file   ModeMovie.cpp
 * \brief  ゲーム中にムービーが流れるシーンで使用するモードです
 * 
 * \author 土居将太郎
 * \date   August 2022
 *********************************************************************/
#include "ModeMovie.h"
#include "ImageServer.h"
#include "Game.h"

ModeMovie::ModeMovie(Game& game,std::string path) :ModeBase{game} ,_sizeX{0},_sizeY{0}
{
	_movieHandle=ImageServer::LoadGraph(path);
	PlayMovieToGraph(_movieHandle);

	GetGraphSize(_movieHandle, &_sizeX, &_sizeY);
}

void ModeMovie::Update() {

}

void ModeMovie::Render() {
	auto scale = static_cast<double>(_sizeY) / static_cast<double>(_sizeX);
	DrawExtendGraph(0,(screen_H-(_sizeY * scale))/2, screen_W / 2, (screen_H - (_sizeY * scale)) / 2+(_sizeY*scale), _movieHandle, 0);
	DrawExtendGraph(screen_W/2, (screen_H - (_sizeY * scale)) / 2,screen_W, (screen_H - (_sizeY * scale)) / 2 + (_sizeY * scale), _movieHandle, 0);
}

void ModeMovie::Debug() {

}
