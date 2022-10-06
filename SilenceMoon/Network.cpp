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
	_analogBuffer.push_back(analog);
	if (_analogBuffer.size() > 10) {
		_analogBuffer.erase(_analogBuffer.begin());
	}
	auto key = _inputManager->GetKeyState();
	_keyBuffer.push_back(key);
	if (_keyBuffer.size() > 10) {
		_keyBuffer.erase(_keyBuffer.begin());
	}

	std::vector<int> rawData;
	rawData.push_back(_game.GetFrameCount());
	for (auto&& value : analog) {
		rawData.push_back(value.Value.x);
		rawData.push_back(value.Value.y);
	}
	for (auto&& value : key) {
		rawData.push_back(value.Hold);
		rawData.push_back(value.Trigger);
		rawData.push_back(value.Release);
	}
	_rawDataBuffer.push_back(rawData);
	if (_rawDataBuffer.size() > 10) {
		_rawDataBuffer.erase(_rawDataBuffer.begin());
	}

	NetWorkSendUDP(_netUDPHandle, _ip, 9850, &_rawDataBuffer, sizeof(_rawDataBuffer));
}

void NetworkJoin::Debug() {
	std::stringstream ss;
	ss << "こっちはジョイン側：接続ハンドル" << _netUDPHandle << "\n";
	for (auto&& keystate : _keyBuffer) {
		for (auto&& key : keystate) {
			ss << key.ActionName << " " << key.Hold << " " << key.Trigger << " " << key.Release << "\n";
		}
		ss << "\n";
	}
	DrawString(50, 0, ss.str().c_str(), GetColor(255, 255, 255));
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
		std::vector<std::vector<int>> recieveData;
		NetWorkRecvUDP(_netUDPHandle, NULL, NULL, &recieveData, 4*71*10*2, FALSE);
		if (recieveData.size() != 0) {
			_rawDataBuffer.insert(_rawDataBuffer.end(), recieveData.begin(), recieveData.end());
			std::sort(_rawDataBuffer.begin(), _rawDataBuffer.end(), CompCountFrame);
			if (_rawDataBuffer.size() >= 10) {
				for (auto itr = _rawDataBuffer.begin() + 9; itr != _rawDataBuffer.end();) {
					itr = _rawDataBuffer.erase(itr);
				}
			}
		}

	}
	std::vector<InputManager::KeyInfo> v_keydata =
	{ { "UP",PAD_INPUT_UP,false,false,false,0 },
		{ "DOWN",PAD_INPUT_DOWN,false,false,false,0 },
		{ "LEFT",PAD_INPUT_LEFT,false,false,false,0 },
		{ "RIGHT",PAD_INPUT_RIGHT,false,false,false,0 },
		{ "ACTION",PAD_INPUT_3,false,false,false,0 },
		{ "PAUSE",PAD_INPUT_8,false,false,false,0 },
		{ "CHANGE",PAD_INPUT_10,false,false,false,0 },
		{ "ACCESS",PAD_INPUT_1,false,false,false,0 },
		{ "DEBUG",PAD_INPUT_7,false,false,false,0 },
		{ "BULLET1",PAD_INPUT_5,false,false,false,0 },
		{ "UP", PAD_INPUT_UP, false, false, false, 1 },
		{ "DOWN",PAD_INPUT_DOWN,false,false,false,1 },
		{ "LEFT",PAD_INPUT_LEFT,false,false,false,1 },
		{ "RIGHT",PAD_INPUT_RIGHT,false,false,false,1 },
		{ "ACTION",PAD_INPUT_3,false,false,false,1 },
		{ "PAUSE",PAD_INPUT_8,false,false,false,1 },
		{ "CHANGE",PAD_INPUT_10,false,false,false,1 },
		{ "ACCESS",PAD_INPUT_1,false,false,false,1 },
		{ "DEBUG",PAD_INPUT_7,false,false,false,1 },
		{ "BULLET1",PAD_INPUT_5,false,false,false,1 },
		{ "BULLET2",PAD_INPUT_6,false,false,false,1 } };

	std::vector < InputManager::AnalogInfo > v_analogdata = {
		{{0,0},0},
		{{0,0},1}
	};

	for (auto&& oneFrameData : _rawDataBuffer) {
		/*ゲーム開始時からのフレーム数*/
		_frameBuffer.push_back(oneFrameData[0]);

		for (int i = 1; i < v_keydata.size() + 1; i = i + 3) {
			int j = i / 3;
			v_keydata[j].Hold = oneFrameData[i];
			v_keydata[j].Trigger = oneFrameData[i + 1];
			v_keydata[j].Release = oneFrameData[i + 2];
		}

		for (int i = oneFrameData.size() - v_analogdata.size(); i < oneFrameData.size(); i = i + 2) {
			int j = i / 2;
			if (i % 2 == 0) {
				v_analogdata[j].Value.x = oneFrameData[i];
				v_analogdata[j].Value.y = oneFrameData[i + 1];
			}

		}
	}
}

void NetworkHost::Debug() {
	std::stringstream ss;
	ss << "こっちはホスト側：接続ハンドル" << _netUDPHandle << "\n";
	for (auto&& keystate : _keyBuffer) {
		for (auto&& key : keystate) {
			ss << key.ActionName << " " << key.Hold << " " << key.Trigger << " " << key.Release << "\n";
		}
		ss << "\n";
	}
	DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
}
