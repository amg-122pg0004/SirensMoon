/*****************************************************************//**
 * \file   ModeMovie.h
 * \brief  �Q�[�����Ƀ��[�r�[�������V�[���Ŏg�p���郂�[�h�ł�
 * 
 * \author �y�������Y
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
