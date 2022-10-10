#include "ModeNetwork.h"
#include "Game.h"
#include <fstream>

ModeNetwork::ModeNetwork(Game& game, ModeBase& mode)
	:ModeBase(game)
	, _preWindow{ mode }
	, _ip{ 192,168,5,214 }
	, _selectIndex{1}
	, _selectMAX{3}

{

	_preWindow.SetStopUpdate(true);
	_renderPriority = 10;
	_keyInputHandle = MakeKeyInput(12, true, false, true);
	SetKeyInputString(IPDATAtoString(_ip), _keyInputHandle);
}

ModeNetwork::~ModeNetwork() {
	_preWindow.SetStopUpdate(false);
}

void ModeNetwork::Update() {
	UpdateSelectIndex();
	if(_game.GetInputManager()->CheckInput("ACCESS", 't', 0)) {
		SelectMenu();
	}
}

void ModeNetwork::Render() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ModeNetwork::Debug() {

}

void ModeNetwork::UpdateSelectIndex() {
	auto analog1 = _game.GetInputManager()->CheckAnalogInput(0);
	if (abs(analog1.y) > 10) {
		_analogFlag = false;
	}
	if (abs(analog1.y) > 800) {
		if (!_analogFlag) {
			_analogFlag = true;
			if (analog1.y > 0) {
				++_selectIndex;
				if (_selectIndex > _selectMAX) {
					_selectIndex = _selectMAX;
				}
				PlaySoundMem(SoundServer::Find("InputDown"), DX_PLAYTYPE_BACK);
			}
			else {
				--_selectIndex;
				if (_selectIndex < 1) {
					_selectIndex = 1;
				}
				PlaySoundMem(SoundServer::Find("InputUp"), DX_PLAYTYPE_BACK);
			}
		}
	}
}

void ModeNetwork::SelectMenu() {
	switch (_selectIndex)
	{
	case(1):
		CreateServer();
		break;
	case(2):
		JoinServer();
		break;
	case(3):
		Back();
		break;
	default:
		break;
	}
}

void ModeNetwork::CreateServer() {

}

void ModeNetwork::JoinServer() {

}

void ModeNetwork::Back() {
	Dead();
}

char* ModeNetwork::IPDATAtoString(IPDATA ip) {
	char string = ip.d1 + ip.d2 + ip.d3 + ip.d4;
	return &string;
}
