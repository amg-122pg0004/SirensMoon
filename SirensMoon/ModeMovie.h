/*****************************************************************//**
 * \file   ModeMovie.h
 * \brief  ゲーム中にムービーが流れるシーンで使用するモードです
 * 
 * \author 土居将太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "ModeBase.h"
#include <string>

class ModeMovie :public ModeBase {
public:
	ModeMovie(Game& game,std::string);

	void Update() override;
	void Render()override;
	void Debug()override;
private:
	int _movieHandle;
	int _sizeX;
	int _sizeY;
};
