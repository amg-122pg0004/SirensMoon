#include "Network.h"
#include "picojson/picojson.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include "Game.h"

NetworkJoin::NetworkJoin(Game& game)
	:_game{ game }, _netHandle{ -1 },_test{false}
{
	_inputManager = _game.GetInputManager();
	Init();

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

	_netHandle = ConnectNetWork(_ip, 9850);
}

void NetworkJoin::Update() {
	_test = false;
	if (_netHandle == -1) {
		return;
	}
	auto analog=_inputManager->GetAnalogState();
	_analogTest[0]=analog[0].Value.x;
	_analogTest[1]=analog[0].Value.y;
	_analogTest[2]=analog[1].Value.x;
	_analogTest[3]=analog[1].Value.y;
	if (_game.GetFrameCount() % 600 == 0) {
		if (NetWorkSend(_netHandle, "繋がったか～！？", 17) == 0) {
			_test = true;
		}
	}

	//NetWorkSend(_netHandle, "", 32);
	//NetWorkSend(_netHandle, &_inputManager->GetAnalogState(), _inputManager->GetAnalogState().size());
	
}

void NetworkJoin::Debug() {
	std::stringstream ss;
	ss << "こっちはジョイン側：接続ハンドル" << _netHandle<<"\n";
	ss << _analogTest[0] << _analogTest[1] << _analogTest[2] << _analogTest[3]<<"\n";
	ss <<"送れていないデータ量" << GetNetWorkSendDataLength(_netHandle)<<"\n";
	if (_test) {
		DrawString(0,150,"送信成功",GetColor(255,255,255));
	}
	DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
}

NetworkHost::NetworkHost(Game& game) :_game{ game }, _netHandle{-1}
{
	Init();
}

void NetworkHost::Init() {
	PreparationListenNetWork(9850);
	_ip = { 0,0,0,0 };
}

void NetworkHost::Update() {
	if (_netHandle == -1) {
		_netHandle = GetNewAcceptNetWork();
		if (_netHandle != -1) {
			StopListenNetWork();
			GetNetWorkIP(_netHandle, &_ip);
		}
	}
	if (_netHandle == -1) {
		return;
	}
	if (GetNetWorkDataLength(_netHandle) != 0) {
		//NetWorkRecv(_netHandle, _analogTest, _dataLength);
		_dataLength = GetNetWorkDataLength(_netHandle);
		NetWorkRecv(_netHandle, StrBuf, _dataLength);
	}
	_lostHandle = GetLostNetWork();
	if (_lostHandle == _netHandle) {
		_ip.d1 = 0;
		_ip.d2 = 0;
		_ip.d3 = 0;
		_ip.d4 = 0;
	}
}

void NetworkHost::Debug() {
	std::stringstream ss;
	ss << "こっちはホスト側：接続ハンドル" << _netHandle<<"\n";
	ss <<"ネットワーク状態　" << GetNetWorkAcceptState(_netHandle)<<"\n";
	/*
	for (auto&& key : _keyBuffer) {
		ss << key.ActionName << " " << key.KeyName << " " << key.Hold << " " << key.Trigger << " " << key.Release << "\n";
	}
	*/
	ss<<static_cast<int>(_ip.d1) << "." << static_cast<int>(_ip.d2) << "." << static_cast<int>(_ip.d3) << "." << static_cast<int>(_ip.d4) << "\n";
	//ss << _analogTest[0]<< _analogTest[1]<< _analogTest[2]<< _analogTest[3];

	DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
	DrawString(50, 200, StrBuf, GetColor(255, 255, 255));
}
