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
	void SendData();
	void RecieveData();
private:
	/**
	フレームデータ 1
	キーデータ 11個
	アナログデータ 2個
	*/
	int _rawDataBuffer[14];

	Game& _game;
	std::shared_ptr<InputManager> _inputManager;
	IPDATA _ip;
	int _netUDPHandle;
	int _dataLength;
};

class NetworkHost {
public:
	NetworkHost(Game& game);
	~NetworkHost();
	void Init();
	void Update();
	void Debug();
	void SendData();
	void RecieveData();
private:
	int _rawDataBuffer[14];
	std::shared_ptr<InputManager> _inputManager;
	std::vector<int> _frameBuffer;
	Game& _game;
	IPDATA _ip;
	int _netUDPHandle;
};