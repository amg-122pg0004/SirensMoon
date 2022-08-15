#pragma once
#include "ModeBase.h"
#include "InputManager.h"

class ModeGameOver :public ModeBase {
public:
	ModeGameOver(Game& game);

	void Update()override;
	void Render()override;

	void RestartGame();

private:

	int _delay;

	std::shared_ptr<InputManager> _inputManager;
	int _movieHandle;

	bool _restart;
};
