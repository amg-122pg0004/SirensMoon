#include "Network.h"
#include "picojson/picojson.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include "Game.h"

NetworkJoin::NetworkJoin(Game& game)
	:_game{ game }, _sendUDPHandle{ -1 },_recieveUDPHandle{-1}
{
	_inputManager = _game.GetInputManager();
	Init();

}
NetworkJoin::~NetworkJoin() {
	DeleteUDPSocket(9850);
}

void NetworkJoin::Init() {

	// ファイルからjsonデータの読み込み
	std::ifstream ifs("resource/ConnectIP.json");
	picojson::value json;
	ifs >> json;
	// jsonデータからパラメータを取得
	picojson::object jsRoot = json.get<picojson::object>();

	_ip.d1 = static_cast<int>(jsRoot["1"].get<double>());
	_ip.d2 = static_cast<int>(jsRoot["2"].get<double>());
	_ip.d3 = static_cast<int>(jsRoot["3"].get<double>());
	_ip.d4 = static_cast<int>(jsRoot["4"].get<double>());

	_sendUDPHandle = MakeUDPSocket(-1);
	_recieveUDPHandle = MakeUDPSocket(9850);
}

void NetworkJoin::Update() {
	SendData();
	RecieveData();
}
void NetworkJoin::SendData() {

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

void NetworkJoin::RecieveData() {
	if (CheckNetWorkRecvUDP(_recieveUDPHandle)) {
		if (NetWorkRecvUDP(_recieveUDPHandle, NULL, NULL, &_rawDataRecieve, 14 * 4, FALSE)) {
			_inputManager->SetUDPData(_rawDataRecieve);
		}
	}
}

void NetworkJoin::Debug() {
	std::stringstream ss;
	ss << "こっちはジョイン側：接続ハンドル" << _sendUDPHandle << "\n";
	for (int i = 0; i < sizeof(_rawDataSend)/sizeof(int); ++i) {
		ss << _rawDataSend[i] << "\n";
	}
	DxLib::DrawString(50, 0, ss.str().c_str(), GetColor(255, 255, 255));
}

NetworkHost::NetworkHost(Game& game) :_game{ game }, _sendUDPHandle{ -1 }, _recieveUDPHandle{ -1 }
{
	_inputManager = _game.GetInputManager();
	Init();
}

NetworkHost::~NetworkHost() {
	DeleteUDPSocket(9850);
}

void NetworkHost::Init() {
	_sendUDPHandle = MakeUDPSocket(-1);
	_recieveUDPHandle= MakeUDPSocket(9850);
	_ip = { 0,0,0,0 };
}

bool CompCountFrame(const std::vector<int>& a, const std::vector<int>& b)
{
	return a[0] < b[0];
}

void NetworkHost::Update() {

	SendData();
	RecieveData();
}

void NetworkHost::SendData() {

	auto analog = _inputManager->GetAnalogState();

	auto key = _inputManager->GetKeyState();
	_rawDataBuffer[0] = _game.GetFrameCount();

	for (auto&& value : analog) {
		if (value.PadNo == 0) {
			_rawDataBuffer[1] = value.Value.x;
			_rawDataBuffer[2] = value.Value.y;
		}
	}
	int i = 3;
	for (auto&& value : key) {
		if (value.PadNo == 0) {
			_rawDataBuffer[i] = value.Hold;
		}
	}
	NetWorkSendUDP(_sendUDPHandle, _ip, 9850, &_rawDataBuffer, 4*14);
}

void NetworkHost::RecieveData() {
	if (CheckNetWorkRecvUDP(_recieveUDPHandle)) {
		NetWorkRecvUDP(_recieveUDPHandle, NULL, NULL, &_rawDataBuffer, 14 * 4, FALSE);
		_inputManager->SetUDPData(_rawDataBuffer);
	}
}

void NetworkHost::Debug() {
	std::stringstream ss;
	ss << "こっちはホスト側：接続ハンドル" << _recieveUDPHandle << "\n";
	for (int i = 0; i < sizeof(_rawDataBuffer) / sizeof(int); ++i) {
		ss << _rawDataBuffer[i] << "\n";
	}

	DxLib::DrawString(300, 100, ss.str().c_str(), GetColor(255, 255, 255));
}