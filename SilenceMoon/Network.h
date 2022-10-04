#pragma once
#include "DxLib.h"
#include "InputManager.h"
#include <memory>
class Game;

class NetworkJoin {
public:
	NetworkJoin(Game& game);
	~NetworkJoin();
	void Init();
	void Update();
	void Debug();
private:
	std::vector<std::vector<InputManager::KeyInfo>> _keyBuffer;
	std::vector < double > _analogBuffer;

	Game& _game;
	std::shared_ptr<InputManager> _inputManager;
	IPDATA _ip;
	int _netUDPHandle;
	int _dataLength;
	bool _test;
	int _analogTest[4];
};

class NetworkHost {
public:
	NetworkHost(Game& game);
	~NetworkHost();
	void Init();
	void Update();
	void Debug();
private:
	std::vector<std::vector<InputManager::KeyInfo>> _keyBuffer;
	std::vector<std::vector < InputManager::AnalogInfo >> _analogBuffer;
	Game& _game;
	IPDATA _ip;
	int _netUDPHandle;
	int _dataLength;
	int _testBuf;
	char StrBuf[256];
};