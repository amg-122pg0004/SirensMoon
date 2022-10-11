#include "Network.h"
#include "picojson/picojson.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include "Game.h"

Network::Network(Game& game)
	:_game{ game }, _sendUDPHandle{ -1 },_recieveUDPHandle{-1}
{
	_inputManager = _game.GetInputManager();
	Init();

}
Network::~Network() {
	DeleteUDPSocket(9850);
}

void Network::Init() {
}

void Network::Update() {
	SendData();
	RecieveData();
}

void Network::SendData() {

	auto analog = _inputManager->GetAnalogState();

	auto key = _inputManager->GetKeyState();
	_rawDataSend[0] = _game.GetFrameCount();

	for (auto&& value : analog) {
		if (value.PadNo == 0) {
			_rawDataSend[1] = value.Value.x;
			_rawDataSend[2] = value.Value.y;
		}
	}
	int i = 3;
	for (auto&& value : key) {
		if (value.PadNo == 0) {
			_rawDataSend[i] = value.Hold;
			++i;
		}
	}
	NetWorkSendUDP(_sendUDPHandle, _ip, 9850, &_rawDataSend, 4*14);
}

void Network::RecieveData() {
	if (CheckNetWorkRecvUDP(_recieveUDPHandle)) {
		if (NetWorkRecvUDP(_recieveUDPHandle, NULL, NULL, &_rawDataRecieve, 14 * 4, FALSE)) {
			_inputManager->SetUDPData(_rawDataRecieve);
		}
	}
}

void Network::Debug() {
	std::stringstream ss;
	ss << "こっちはジョイン側：接続ハンドル" << _sendUDPHandle << "\n";
	for (int i = 0; i < sizeof(_rawDataSend)/sizeof(int); ++i) {
		ss << _rawDataSend[i] << "\n";
	}
	DxLib::DrawString(300, 100, ss.str().c_str(), GetColor(255, 255, 255));
}

bool CompCountFrame(const std::vector<int>& a, const std::vector<int>& b)
{
	return a[0] < b[0];
}