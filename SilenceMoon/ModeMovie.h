/*****************************************************************//**
 * \file   ModeMovie.h
 * \brief  ゲーム中にムービーが流れるシーンで使用するモードです
 * 
 * \author 土居将太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "ModeBase.h"
#include "SplitWindow.h"
#include <string>

class UIBase;

class ModeMovie :public ModeBase {
public:
	ModeMovie(Game& game,std::string,int startFrame,int skipFrame,bool splitFlag);
	~ModeMovie();
	void Update() override;
	void Render()override;
	void Debug()override;
	void SetBGM(std::string path,int frame);
	void PlayBGMInSetFrame();
private:
	void VisibleSkipUI();
	bool _splitFlag;
	int _movieHandle;
	int _movieSkipFrame;
	int _sizeX;
	int _sizeY;

	std::string _path;
	std::string _bgm;
	int _bgmPlayFrame;
	std::vector<std::unique_ptr<UIBase>> _ui;
	int _loadingNumber;
	std::unique_ptr<SplitWindow> _splitWindow;
};
