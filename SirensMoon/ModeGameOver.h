#pragma once
#include "ModeBase.h"
#include "InputManager.h"
#include "UIBase.h"

class ModeGameOver :public ModeBase {
public:
	ModeGameOver(Game& game);

	void Update()override;
	void Render()override;

	void RestartGame();

private:

	std::shared_ptr<InputManager> _inputManager;
	std::vector<std::unique_ptr<UIBase>> _ui;

};
