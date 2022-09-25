#pragma once
#include <DxLib.h>
#include "ModeBase.h"
#include "InputManager.h"
#include "ImageServer.h"
#include "SoundServer.h"

class ModeStartUp2 :public ModeBase {
public:
	ModeStartUp2(Game& game);
	void Update()override;
	void Render()override;
	void Debug()override;
private:
	std::shared_ptr<InputManager> _inputManager;
	int _movieHandle;

	bool _pushPlayerA,_pushPlayerB;

	int _cg_red;
	int _cg_blue;
};
