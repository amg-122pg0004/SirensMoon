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
	data.length = sizeof(data);
	data.frame = _game.GetFrameCount();
	data.key = keyData;
	data.analog = analogData;
	NetWorkSend(_netTCPHandle, &data, data.length);
}

InputData Network::RecieveInputData() {
	InputData data;
	data.frame = -1;
	auto length=GetNetWorkSendDataLength(_netTCPHandle);
	if (length !=0)
	{
		NetWorkRecvToPeek(_netTCPHandle, &data, length);
	}
	return data;
}

void Network::Debug() {
	if (_reciveError) {
		DrawStringF(500, 0, "データ受け取りエラー", GetColor(255, 0, 0));
	}
	//DrawString(500, 0, ss.str().c_str(), GetColor(255, 255, 255));
}