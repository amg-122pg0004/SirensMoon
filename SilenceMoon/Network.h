#pragma once
#include "DxLib.h"
#include "InputManager.h"
#include <memory>
#include <array>
class Game;

class Network {
public:
	Network(Game& game);
	~Network();
	void Update();
	void Debug();
	void SendData();
	void RecieveData();

	void SetIP(IPDATA ip) { _ip = ip; }
	void SetPortNo(int port) { _port = port; }
	void SetNetTCPHandle(int tcp) { _netTCPHandle = tcp; }
	void SetSendUDPHandle(int sendUDP) { _sendUDPHandle = sendUDP; }
	void SetRecieveUDPHandle(int recieveUDP) { _recieveUDPHandle = recieveUDP; }

	void SendTCPData(void* sendData);
	void* RecieveTCPData();
private:
	/**
	�t���[���f�[�^ 1
	�L�[�f�[�^ 11��
	�A�i���O�f�[�^ 2��
	*/
	std::array<std::array<int, 14>, 10> _rawDataSendBuffer;
	std::vector<std::array<int, 14>> _rawDataRecieveBuffer;
	Game& _game;
	std::shared_ptr<InputManager> _inputManager;

	IPDATA _ip;
	int _port;
	int _netTCPHandle;
	int _sendUDPHandle, _recieveUDPHandle;

	int _reciveDataFrameCount;//�󂯎�����f�[�^�Ŏg�p���Ă���t���[���J�E���g
	bool _reciveError;//<�G���[���b�Z�[�W�p
};