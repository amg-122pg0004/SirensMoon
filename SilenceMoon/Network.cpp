#include "Network.h"
#include "picojson/picojson.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include "Game.h"

Network::Network(Game& game)
	:_game{ game }, _sendUDPHandle{ -1 }, _recieveUDPHandle{ -1 }
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

void Network::RecieveData() {
	if (CheckNetWorkRecvUDP(_recieveUDPHandle)) {
		 std::array<std::array<int, 14>,10> recieveData;
		if (NetWorkRecvUDP(_recieveUDPHandle, NULL, NULL, &recieveData, 14 * 4 * 10, FALSE)) {
			for (auto itr = recieveData.begin(); itr != recieveData.end();++itr) {
				for (auto&& ahaveData : _rawDataRecieveBuffer) {
					if (*itr[0] == ahaveData[0]) {
						aInputData
					}
				}
			}
			std::sort(_rawDataRecieveBuffer.begin(), _rawDataRecieveBuffer.end(), CompCountFrame);
			_inputManager->SetUDPData(_rawDataRecieve);

		}
	}
}

void Network::Debug() {

}

bool CompCountFrame(const std::vector<int>& a, const std::vector<int>& b)
{
	return a[0] < b[0];
}