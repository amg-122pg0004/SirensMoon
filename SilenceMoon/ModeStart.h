#pragma once
#include <DxLib.h>
#include "ModeBase.h"
#include "InputManager.h"
#include "ImageServer.h"
#include "SoundServer.h"
#include "SplitWindow.h"

class UIBase;

class ModeStart:public ModeBase{
public:
	ModeStart(Game& game,int seekmovie);
	void Update()override;
	void Render()override;
	void Debug()override;
	void Play();
private:
	void Credit();
	void Quit();
	void NetWork();
	void VisibleSkipUI();
	
	bool _analogFlag1,_analogFlag2;//<�A�i���O���͂���ꂽ�ꍇ�̃t���O
	std::shared_ptr<InputManager> _inputManager;
	int _movieHandle;
	int _select;//<�I���ʒu

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

	/*�X�L�b�vUI�p*/
	std::vector<std::unique_ptr<UIBase>> _ui;
	int _loadingNumber;
	std::unique_ptr<SplitWindow> _splitWindow;

	int _font;
};