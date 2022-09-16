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
	ModeMovie(Game& game,std::string,int skipFrame,bool splitFlag);
	void Update() override;
	void Render()override;
	void Debug()override;
	void SetBGM(std::string path,int frame);
	void PlayBGMInSetFrame();
private:
	bool _splitFlag;
	int _movieHandle;
	int _movieSkipFrame;
	int _sizeX;
	int _sizeY;

	std::string _bgm;
	int _bgmPlayFrame;
};
