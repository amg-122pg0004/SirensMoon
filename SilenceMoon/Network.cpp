#include "Network.h"
#include "picojson/picojson.h"
#include "InputManager.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include "Game.h"

Network::Network(Game& game)
	:_game{ game }
	, _sendUDPHandle{ -1 }
	, _recieveUDPHandle{ -1 }
	, _reciveDataFrameCount{ -1 }
	, _reciveError{ false }
{
	_inputManager = _game.GetInputManager();

}
Network::~Network() {
	DeleteUDPSocket(_port);
}

void Network::SendInputData(int keyData, Vector2 analogData) {
	InputData data;
	data.type = DataType::InputData;
	data.length = sizeof(InputData);
	data.frame = _game.GetFrameCount();
	data.key = keyData;
	data.analog = analogData;
	NetWorkSend(_netTCPHandle, &data, data.length);
}

void Network::SendEnemyData(int* enemyData) {
	EnemyGenerateData data;
	data.type = DataType::EnemyGenerate;
	for (int i = 0; i < 255; ++i) {
		//data.data[i] = enemyData[i];
		data.data[i] = 1;
	}
	data.length = sizeof(EnemyGenerateData);
	NetWorkSend(_netTCPHandle, &data, data.length);
}

InputData Network::RecieveInputData() {
	NetworkDataBase base;
	InputData data;

	auto length= GetNetWorkDataLength(_netTCPHandle);
	if (length >=sizeof(NetworkDataBase))
	{
		NetWorkRecvToPeek(_netTCPHandle, &base, sizeof(NetworkDataBase));
		switch (base.type)
		{
		case DataType::InputData:
			if (GetNetWorkDataLength(_netTCPHandle) >= base.length) {
				NetWorkRecv(_netTCPHandle, &data, sizeof(InputData));
				return 	data;
			}
		case DataType::EnemyGenerate:
			EnemyGenerateData enemyData;
			if (GetNetWorkDataLength(_netTCPHandle) >= base.length) {
				NetWorkRecv(_netTCPHandle, &enemyData, sizeof(EnemyGenerateData));
			}
			break;
		default:
			break;
		}

	}
	data.frame = -1;
	return data;
}

void Network::Debug() {
	if (_reciveError) {
		DrawStringF(500, 0, "データ受け取りエラー", GetColor(255, 0, 0));
	}
	//DrawString(500, 0, ss.str().c_str(), GetColor(255, 255, 255));
}