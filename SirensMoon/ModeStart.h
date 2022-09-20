#pragma once
#include <DxLib.h>
#include "ModeBase.h"
#include "InputManager.h"
#include "ImageServer.h"
#include "SoundServer.h"

class UIBase;

class ModeStart:public ModeBase{
public:
	ModeStart(Game& game,int seekmovie);
	void Update()override;
	void Render()override;
	void Debug()override;
private:
	void Play();
	void Credit();
	void Quit();
	void VisibleSkipUI();
	
	bool _analogFlag1,_analogFlag2;//<アナログ入力を入れた場合のフラグ
	std::shared_ptr<InputManager> _inputManager;
	int _movieHandle;
	int _select;//<選択位置

	Vector2 _pos;

	bool _bgm;

	int _cg_bg;
	int _cg_logo;
	int _cg_cursor;
	std::pair<int, int> _cg_start;
	std::pair<int, int> _cg_credit;
	std::pair<int, int> _cg_quit;
	int _cg2pFrame,_cg2pText;

	int _alpha;

	/*スキップUI用*/
	std::vector<std::unique_ptr<UIBase>> _ui;
	int _loadingNumber;
};