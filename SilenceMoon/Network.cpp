#include "Network.h"
#include "picojson/picojson.h"
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
	, _reciveDataFrameCount{-1}
	,_reciveError{false}
{
	for (int i = 0; i < _rawDataSendBuffer.size(); ++i) {
		std::fill(_rawDataSendBuffer[i].begin(), _rawDataSendBuffer[i].end(), -1);
	}
	_inputManager = _game.GetInputManager();

}
Network::~Network() {
	DeleteUDPSocket(9850);
}

void Network::Update() {
	SendData();
	RecieveData();
}

void Network::SendData() {
	std::rotate(_rawDataSendBuffer.rbegin(), _rawDataSendBuffer.rbegin() + 1, _rawDataSendBuffer.rend());
	auto analog = _inputManager->GetAnalogState();
	auto key = _inputManager->GetKeyState();

	_rawDataSendBuffer[0][0] = _game.GetFrameCount();

	for (auto&& value : analog) {
		if (value.PadNo == 0) {
			_rawDataSendBuffer[0][1] = value.Value.x;
			_rawDataSendBuffer[0][2] = value.Value.y;
		}
	}
	int i = 3;
	for (auto&& value : key) {
		if (value.PadNo == 0) {
			_rawDataSendBuffer[0][i] = value.Hold;
			++i;
		}
	}

	NetWorkSendUDP(_sendUDPHandle, _ip, 9850, &_rawDataSendBuffer, 4 * 14 * 10);
}

bool CompCountFrame(const std::array<int, 14>& a, const std::array<int, 14>& b)
{
	return a[0] < b[0];
}

void Network::RecieveData() {
	if (CheckNetWorkRecvUDP(_recieveUDPHandle)) {
		std::vector<std::array<int, 14>> recieveData;
		if (NetWorkRecvUDP(_recieveUDPHandle, NULL, NULL, &recieveData, 14 * 4 * 10, FALSE)) {
			for (auto itr = recieveData.begin(); itr != recieveData.end(); ++itr) {
				for (auto&& ahaveData : _rawDataRecieveBuffer) {
					if (*itr->begin()== ahaveData[0]) {
						itr = recieveData.erase(itr);
					}
				}
			}
			_rawDataRecieveBuffer.insert(_rawDataRecieveBuffer.end(), recieveData.begin(), recieveData.end());
			std::sort(_rawDataRecieveBuffer.begin(), _rawDataRecieveBuffer.end(), CompCountFrame);
			if (_reciveDataFrameCount == -1) {
				_reciveDataFrameCount = *_rawDataRecieveBuffer.begin()->begin();
			}
			else {
				++_reciveDataFrameCount;
			}
			auto result = std::find_if(_rawDataRecieveBuffer.begin()
				, _rawDataRecieveBuffer.end()
				, [this](std::array<int, 14> data) {return data[0] == _reciveDataFrameCount; });
			if (result != _rawDataRecieveBuffer.end()) {
				_inputManager->SetUDPData(*result);
				_reciveError = false;

			}
			else {
				_reciveError = true;
			}
			_rawDataRecieveBuffer.erase(_rawDataRecieveBuffer.begin(), result);
		}
	}
}

void Network::Debug() {
	if (_reciveError) {
		DrawStringF(0, 500, "データ受け取りエラー", GetColor(255, 0, 0));
	}
}
