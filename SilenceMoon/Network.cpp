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
	,_fixPosition{-1.0,-1.0}
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

void Network::GenerateAndSendRandomData() {

	RandomData data;
	data.type = DataType::RandomData;
	data.length=sizeof(RandomData);
	std::random_device rnd;
	std::mt19937 engine(rnd());
	data.random = engine();
	_randomBuffer.push_back(data.random);
	NetWorkSend(_netTCPHandle, &data, data.length);
}

void Network::SendPositionFixData(Vector2 position) {
	PositionFixData data;
	data.type = DataType::PositionFix;
	data.length = sizeof(PositionFixData);
	data.Position = position;
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
				NetWorkRecv(_netTCPHandle, &data, base.length);
				return 	data;
			}
		case DataType::RandomData:
			RandomData random;
			if (GetNetWorkDataLength(_netTCPHandle) >= base.length) {
				NetWorkRecv(_netTCPHandle, &random, base.length);
				_randomBuffer.push_back(random.random);
			}
		case DataType::PositionFix:
			PositionFixData fixpos;
			if (GetNetWorkDataLength(_netTCPHandle) >= base.length) {
				NetWorkRecv(_netTCPHandle, &fixpos, base.length);
				_fixPosition = fixpos.Position;
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

unsigned int Network::GetRandomData(){
	if (_randomBuffer.size() == 0) {
		return -1;
	}
	auto getData = _randomBuffer.back();
	_randomBuffer.erase(_randomBuffer.end()-1);
	return getData;
}

Vector2 Network::GetFixPosition(){
	if (_fixPosition.x != -1.0 && _fixPosition.y != -1.0) {
		return _fixPosition;
	}
	Vector2 getData = _fixPosition;
	_fixPosition = { -1.0,-1.0 };
	return getData;
}
