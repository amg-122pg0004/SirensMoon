#pragma once
#include "DxLib.h"
#include "InputManager.h"
#include <memory>
class Game;

class Network {
public:
	Network(Game& game);
	~Network();
	void Init();
	void Update();
	void Debug();
	void SendData();
	void RecieveData();

	void SetIP(IPDATA ip) { _ip = ip; }
	void SetPortNo(int port) { _port = port; }
	void SetNetTCPHandle(int tcp) { _netTCPHandle=tcp; }
	void SetSendUDPHandle(int sendUDP) { _sendUDPHandle = sendUDP; }
	void SetRecieveUDPHandle(int recieveUDP) { _recieveUDPHandle = recieveUDP; }
private:
	/**
	フレームデータ 1
	キーデータ 11個
	アナログデータ 2個
	*/
	int _rawDataSend[14];
	int _rawDataRecieve[14];
	Game& _game;
	std::shared_ptr<InputManager> _inputManager;

	IPDATA _ip;
	int _port;
	int _netTCPHandle;
	int _sendUDPHandle,_recieveUDPHandle;
	int _dataLength;
};