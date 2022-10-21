#pragma once
#include "DxLib.h"
#include "NetDataStructs.h"
#include <memory>
#include <array>
class Game;
class InputManager;

class Network {
public:
	Network(Game& game);
	~Network();
	void Debug();
	void SendInputData(int keyData,Vector2 analogData);
	void GenerateAndSendRandomData();
	InputData RecieveInputData();

	void SetIP(IPDATA ip) { _ip = ip; }
	void SetPortNo(int port) { _port = port; }
	void SetNetTCPHandle(int tcp) { _netTCPHandle = tcp; }
	void SetRecieveUDPHandle(int recieveUDP) { _recieveUDPHandle = recieveUDP; }
	void SetSendUDPHandle(int sendUDP) { _sendUDPHandle = sendUDP; }
	unsigned int GetRandomData();
private:
	Game& _game;
	std::shared_ptr<InputManager> _inputManager;


	IPDATA _ip;
	int _port;
	int _netTCPHandle;
	int _sendUDPHandle, _recieveUDPHandle;

	int _reciveDataFrameCount;//受け取ったデータで使用しているフレームカウント
	bool _reciveError;//<エラーメッセージ用

	std::vector<unsigned int> _randomBuffer;
};