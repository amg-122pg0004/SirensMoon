#include "Network.h"
#include "picojson/picojson.h"
#include <fstream>
#include "Game.h"

NetworkJoin::NetworkJoin(Game& game)
	:_game{game},_netHandle { -1 }
{
	_inputManager = _game.GetInputManager();
	Init();
	_netHandle = ConnectNetWork(_ip, 9850);
}
void NetworkJoin::Init() {


	// �t�@�C������json�f�[�^�̓ǂݍ���
	std::ifstream ifs("resource/ConnectIP.json");
	picojson::value json;
	ifs >> json;
	// json�f�[�^����p�����[�^���擾
	picojson::object jsRoot = json.get<picojson::object>();

	_ip.d1 = static_cast<int>(jsRoot["1"].get<double>());
	_ip.d2 = static_cast<int>(jsRoot["2"].get<double>());
	_ip.d3 = static_cast<int>(jsRoot["3"].get<double>());
	_ip.d4 = static_cast<int>(jsRoot["4"].get<double>());
}
void NetworkJoin::Update(){
	if (_netHandle == -1) {
		return;
	}

	NetWorkSend(_inputManager->);
}
