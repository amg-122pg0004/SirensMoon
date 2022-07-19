#pragma once
#include "Actor.h"
#include "InputManager.h"
#include "Game.h"
#include "Math.h"
#include "LightBase.h"
#include <memory>

class ModeBase;

class ReconPlayer :public Actor {
public:
	ReconPlayer(Game& game,ModeBase& mode, int playernum);
	void Update() override;
	void ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;
	Type GetType() override { return Type::ReconPlayer; }
private:
	std::shared_ptr<InputManager> _inputManager;
	Vector2 _dir;
	int _speed;
	int _playerNum;
	int _cg_recon;
};