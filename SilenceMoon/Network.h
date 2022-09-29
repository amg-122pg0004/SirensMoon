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
	void Debug();
private:
	std::vector<std::vector<InputManager::KeyInfo>> _keyBuffer;
	std::vector < double > _analogBuffer;

	Game& _game;
	std::shared_ptr<InputManager> _inputManager;
	IPDATA _ip;
	int _netHandle;
	int _dataLength;
	double _analogTest[4];
	bool _test;
};

class NetworkHost {
public:
	NetworkHost(Game& game);
	void Init();
	void Update();
	void Debug();
private:
	//std::vector<double> _keyBuffer;
	std::vector < double > _analogBuffer;
	double _analogTest[4];
	char StrBuf[256];

	Game& _game;
	IPDATA _ip;
	int _netHandle,_lostHandle;
	int _dataLength;
};