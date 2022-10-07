#include "Network.h"
#include "picojson/picojson.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include "Game.h"

NetworkJoin::NetworkJoin(Game& game)
	:_game{ game }, _netUDPHandle{ -1 }, _test{ false }
{
	_inputManager = _game.GetInputManager();
	Init();

}
NetworkJoin::~NetworkJoin() {
	DeleteUDPSocket(-1);
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

	_netUDPHandle = MakeUDPSocket(-1);
}

void NetworkJoin::Update() {
	_test = false;

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
	NetWorkSendUDP(_netUDPHandle, _ip, 9850, &_rawDataBuffer, 4);
}

void NetworkJoin::Debug() {
	std::stringstream ss;
	ss << "こっちはジョイン側：接続ハンドル" << _netUDPHandle << "\n";
	for (int i = 0; i < sizeof(_rawDataBuffer)/sizeof(int); ++i) {
		ss << _rawDataBuffer[i] << "\n";
	}
	DxLib::DrawString(50, 0, ss.str().c_str(), GetColor(255, 255, 255));
}

NetworkHost::NetworkHost(Game& game) :_game{ game }, _netUDPHandle{ -1 }
{
	Init();
}

NetworkHost::~NetworkHost() {
	DeleteUDPSocket(9850);
}

void NetworkHost::Init() {
	_netUDPHandle = MakeUDPSocket(9850);
	_ip = { 0,0,0,0 };
}

bool CompCountFrame(const std::vector<int>& a, const std::vector<int>& b)
{
	return a[0] < b[0];
}

void NetworkHost::Update() {

	if (CheckNetWorkRecvUDP(_netUDPHandle)) {
		NetWorkRecvUDP(_netUDPHandle, NULL, NULL, &_rawDataBuffer, 14*4, FALSE);

	}
}

void NetworkHost::Debug() {
	std::stringstream ss;
	ss << "こっちはホスト側：接続ハンドル" << _netUDPHandle << "\n";
	for (int i = 0; i < sizeof(_rawDataBuffer) / sizeof(int); ++i) {
		ss << _rawDataBuffer[i] << "\n";
	}

	DxLib::DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
}