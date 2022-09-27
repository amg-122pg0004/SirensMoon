#pragma once
#include "DxLib.h"
#include "InputManager.h"
#include <memory>
class Game;

class NetworkJoin {
public:
	NetworkJoin(Game& game);
	void Init();
	void Update();
private:
	std::vector<std::vector<InputManager::KeyInfo>> _keyBuffer;
	std::vector<std::vector < InputManager::AnalogInfo >> _analogBuffer;

	Game& _game;
	std::shared_ptr<InputManager> _inputManager;
	IPDATA _ip;
	int _netHandle;
	int _dataLength;
};

class NetworkHost {
public:

private:
	std::vector<std::vector<InputManager::KeyInfo>> _keyBuffer;
	std::vector<std::vector < InputManager::AnalogInfo >> _analogBuffer;

	IPDATA _ip;
	int _netHandle,_lostHandle;
	int _dataLength;
};