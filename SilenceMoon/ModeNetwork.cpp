#include "ModeNetwork.h"
#include "Game.h"
#include "ModeStart.h"
#include <array>
#include <fstream>

ModeNetwork::ModeNetwork(Game& game, ModeBase& mode)
	:ModeBase(game)
	, _preWindow{ mode }
	, _state{ State::NotTryConnect }
	, _ip{ 192,168,5,214 }
	, _port{ 9850 }
	, _selectIndex{ 0 }
	, _selectMAX{ 4 }
	, _analogFlag{ false }
	, _connectError{ false }
	, _netTCPHandle{ -1 }
	, _netUDPRecieveHandle{ -1 }
	, _netUDPSendHandle{ -1 }
	, _settingIPIndex{ 0 }
	, _keyInputHandlesIP{ -1,-1,-1,-1 }
	, _keyInputHandlePort{ -1 }
	, _dataLength{ 0 }
{
	_font = CreateFontToHandle("OPTION", 52, 10, DX_FONTTYPE_EDGE);
	_preWindow.SetStopUpdate(true);
	_renderPriority = 10;
	for (auto&& handle : _keyInputHandlesIP) {
		handle = MakeKeyInput(3, true, false, true);
	}
	_keyInputHandlePort = MakeKeyInput(5, true, false, true);
}

ModeNetwork::~ModeNetwork() {
	_preWindow.SetStopUpdate(false);
}

void ModeNetwork::Update() {
	UpdateSelectIndex();
	if (_game.GetInputManager()->CheckInput("ACCESS", 't', 0)) {
		SelectMenu();
	}
	if (_state == State::SettingIP) {
		ActiveInputIP();
	}
	if (_state == State::SettingPort) {
		ActiveInputPort();
	}

	if (_state == State::WaitAccept) {
		WaitAcceptNet();
	}
	if (_state == State::JoinComplete || _state == State::AcceptComplete) {
		StartGame();
	}
}

void ModeNetwork::Render() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DxLib::DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


	Vector2 textPosition{ 200,200 };
	int textSpace{ 100 };
	std::array<std::string, 5> textList{
		"サーバーの作成"
		, "サーバーへの接続"
		, "接続IP" + std::to_string(_ip.d1) + '.' + std::to_string(_ip.d2) + '.' + std::to_string(_ip.d3) + '.' + std::to_string(_ip.d4)
		, "使用ポート" + std::to_string(_port)
		, "戻る" };

	for (int i = 0; i < textList.size(); ++i) {
		DrawStringToHandle(static_cast<int>(textPosition.x)
			, static_cast<int>(textPosition.y) + textSpace * i
			, textList[i].c_str()
			, GetColor(255, 255, 255)
			, _font);
	}
	int size{ 0 };
	DxLib::GetFontStateToHandle(NULL, &size, NULL, _font);

	DxLib::DrawBox(static_cast<int>(textPosition.x)
		, static_cast<int>(textPosition.y) + textSpace * _selectIndex
		, static_cast<int>(textPosition.x) + size * static_cast<int>(textList[_selectIndex].length())
		, static_cast<int>(textPosition.y) + textSpace * _selectIndex + size
		, GetColor(255, 255, 255), false);

	if (_state == State::WaitAccept) {
		Vector2 textPosition2{ 0,0 };
		DrawStringToHandle(static_cast<int>(textPosition2.x)
			, static_cast<int>(textPosition2.y)
			, "接続待機中"
			, GetColor(255, 255, 255)
			, _font);
	}
	if (_connectError) {
		Vector2 textPosition2{ 0,0 };
		DrawStringToHandle(static_cast<int>(textPosition2.x)
			, static_cast<int>(textPosition2.y)
			, "接続エラー"
			, GetColor(255, 255, 255)
			, _font);
	}
	if (_state == State::SettingIP) {
		DrawKeyInputModeString(0, 0);
		for (int i = 0; i < _keyInputHandlesIP.size(); ++i) {
			DrawKeyInputString(50 * i, 50, _keyInputHandlesIP[i]);
			int number{ 0 };
			number = GetKeyInputNumber(_keyInputHandlesIP[i]);
			DrawStringToHandle(100
				, 900 + 100 * i
				, "" + number
				, GetColor(255, 255, 255)
				, _font);
		}

	}
	if (_state == State::SettingPort) {
		DrawKeyInputModeString(0, 0);
		DrawKeyInputString(0, 50, _keyInputHandlePort);
	}
}

void ModeNetwork::Debug() {
	std::stringstream ss;
	ss << "_netTCPHandle" << _netTCPHandle << "\n";
	ss << "_netUDPSendHandle" << _netUDPSendHandle << "\n";
	ss << "_netUDPRecieveHandle" << _netUDPRecieveHandle << "\n";
	DxLib::DrawString(900, 100, ss.str().c_str(), GetColor(255, 255, 255));
}

void ModeNetwork::UpdateSelectIndex() {
	auto analog1 = _game.GetInputManager()->CheckAnalogInput(0);
	if (abs(analog1.y) < 10) {
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
				if (_selectIndex < 0) {
					_selectIndex = 0;
				}
				PlaySoundMem(SoundServer::Find("InputUp"), DX_PLAYTYPE_BACK);
			}
		}
	}
}

void ModeNetwork::SelectMenu() {
	switch (_selectIndex)
	{
	case(0):
		CreateServer();
		break;
	case(1):
		JoinServer();
		break;
	case(2):
		SettingIP();
		break;
	case(3):
		SettingPort();
		break;
	case(4):
		Back();
		break;
	default:
		break;
	}
}

void ModeNetwork::CreateServer() {
	PreparationListenNetWork(_port);
	//_netUDPRecieveHandle = MakeUDPSocket(_port);
	//_netUDPSendHandle = MakeUDPSocket(-1);
	_state = State::WaitAccept;
}

void ModeNetwork::JoinServer() {
	_netTCPHandle = ConnectNetWork(_ip, _port);
	if (_netTCPHandle != -1) {
		int call{ 1234 };
		NetWorkSend(_netTCPHandle, &call, 4);
	}
	int react{ 0 };
	if (react != 0) {
		_state = State::JoinComplete;
		_game.GetInputManager()->SetOnline(2);
	}

}

void ModeNetwork::SettingIP() {
	_state = State::SettingIP;
	_settingIPIndex = 0;
	for (auto&& handle : _keyInputHandlesIP) {
		DeleteKeyInput(handle);
	}
	SetActiveKeyInput(_keyInputHandlesIP[_settingIPIndex]);
}

void ModeNetwork::SettingPort() {
	_state = State::SettingPort;
	DeleteKeyInput(_keyInputHandlePort);
	SetActiveKeyInput(_keyInputHandlePort);
}

void ModeNetwork::Back() {
	Dead();
}

void ModeNetwork::WaitAcceptNet() {
	int netTCPRecieveHandle{ -1 };
	netTCPRecieveHandle == GetNewAcceptNetWork();
	if (netTCPRecieveHandle != -1) {
		_netTCPHandle == netTCPRecieveHandle;
		StopListenNetWork();
		GetNetWorkIP(_netTCPHandle, &_ip);
	}
	if (_netTCPHandle != -1) {
		_dataLength = GetNetWorkDataLength(_netTCPHandle);
		if (_dataLength != 0) {
			int react{ 0 };
			NetWorkRecv(_netTCPHandle, &react, _dataLength);
			if (react == 1234) {
				_state = State::AcceptComplete;
			}
		}
	}
}

void ModeNetwork::StartGame() {
	/*
	_game.StartNetwork();
	_game.GetNetwork()->SetIP(_ip);
	_game.GetNetwork()->SetPortNo(_port);
	_game.GetNetwork()->SetNetTCPHandle(_netTCPRecieveHandle);
	_game.GetNetwork()->SetSendUDPHandle(_netUDPSendHandle);
	_game.GetNetwork()->SetRecieveUDPHandle(_netUDPRecieveHandle);
	Dead();
	static_cast<ModeStart&>(_preWindow).Play();
	*/
}

void ModeNetwork::ActiveInputIP() {
	if (CheckKeyInput(_keyInputHandlesIP[_settingIPIndex]) == 1) {
		int ip = GetKeyInputNumber(_keyInputHandlesIP[_settingIPIndex]);
		switch (_settingIPIndex) {
		case(0):
			_ip.d1 = ip;
			break;
		case(1):
			_ip.d2 = ip;
			break;
		case(2):
			_ip.d3 = ip;
			break;
		case(3):
			_ip.d4 = ip;
			break;
		}

		if (_settingIPIndex < 3) {
			++_settingIPIndex;
			SetActiveKeyInput(_keyInputHandlesIP[_settingIPIndex]);
		}
	}
}

void ModeNetwork::ActiveInputPort() {
	if (CheckKeyInput(_keyInputHandlePort) == 1) {
		_port = GetKeyInputNumber(_keyInputHandlePort);
	}
}
