#pragma once
#include <DxLib.h>
#include "ModeBase.h"
#include "InputManager.h"
#include "ImageServer.h"
#include "SoundServer.h"

class ModeStart:public ModeBase{
public:
	ModeStart(Game& game);
	void Update()override;
	void Render()override;
	void Debug()override;
private:
	void Play();
	void Credit();
	void Quit();

	
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

	int _alpha;
};
