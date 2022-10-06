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
	/**
	フレームデータ 1
	キーデータ 33個
	アナログデータ 4個
	*/
	std::vector<std::vector<int>> _rawDataBuffer;

	/*10f分のキー入力保持*/
	std::vector<std::vector<InputManager::KeyInfo>> _keyBuffer;
	std::vector < std::vector<InputManager::AnalogInfo> > _analogBuffer;

	Game& _game;
	std::shared_ptr<InputManager> _inputManager;
	IPDATA _ip;
	int _netUDPHandle;
	int _dataLength;
	bool _test;
};

class NetworkHost {
public:
	NetworkHost(Game& game);
	~NetworkHost();
	void Init();
	void Update();
	void Debug();
private:
	std::vector<std::vector<int>> _rawDataBuffer;
	std::vector<int> _frameBuffer;
	std::vector<std::vector<InputManager::KeyInfo>> _keyBuffer;
	std::vector<std::vector < InputManager::AnalogInfo >> _analogBuffer;
	Game& _game;
	IPDATA _ip;
	int _netUDPHandle;
	int _dataLength;
};