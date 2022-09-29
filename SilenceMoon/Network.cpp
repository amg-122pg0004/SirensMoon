#include "Network.h"
#include "picojson/picojson.h"
#include <fstream>
#include <sstream>
#include "Game.h"

NetworkJoin::NetworkJoin(Game& game)
	:_game{game},_netHandle { -1 }
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

void NetworkJoin::Update(){
	if (_netHandle == -1) {
		return;
	}

	NetWorkSend(_netHandle,_inputManager->GetKeyState().data(), static_cast<int>(_inputManager->GetKeyState().size()));
	//NetWorkSend(_netHandle, &_inputManager->GetAnalogState(), _inputManager->GetAnalogState().size());
}


NetworkHost::NetworkHost(Game& game):_game{game}
{
	Init();
}

void NetworkHost::Init() {
	PreparationListenNetWork(9850);
	_ip = { 0,0,0,0 };
}

void NetworkHost::Update(){
	_netHandle = GetNewAcceptNetWork();
	if (_netHandle == -1) {
		return;
	}
	if (_ip.d1==0&&_ip.d2==0,_ip.d3==0&&_ip.d4==0) {
		StopListenNetWork();
		GetNetWorkIP(_netHandle, &_ip);
	}
	else {
		_dataLength = GetNetWorkDataLength(_netHandle);
		NetWorkRecv(_netHandle, &_keyBuffer, _dataLength);
		_lostHandle = GetLostNetWork();
		if (_lostHandle == _netHandle) {

		}
	}

}

void NetworkHost::Debug(){
	std::stringstream ss;
	for (auto&& key : _keyBuffer) {
		ss << key.ActionName << " " << key.KeyName << " " << key.Hold << " " << key.Trigger << " " << key.Release << "\n";
	}
	/*
	for (auto&& analog : _analogBuffer) {
		ss << "アナログスティックプレイヤー" << analog.PadNo << " " << analog.Value.x << " " << analog.Value.y << "\n";
	}
	*/
	DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
}
