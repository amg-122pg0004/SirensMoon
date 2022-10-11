#pragma once
#include "ModeBase.h"
#include <functional>
#include <array>
class Game;

class ModeNetwork :public ModeBase {
public:
	ModeNetwork(Game& game, ModeBase& mode);
	~ModeNetwork();
	void Update()override;
	void Render()override;
	void Debug()override;

	/*Update中の関数*/
	void UpdateSelectIndex();
	void SelectMenu();
	void FinishKeyInput();


	void CreateServer();
	void JoinServer();
	void SettingIP();
	void ActiveInputIP();
	void SettingPort();
	void ActiveInputPort();
	void Back();
	void StartGame();
	void WaitAcceptNet();


	enum class State {
		NotTryConnect,
		WaitAccept,
		AcceptComplete,
		JoinComplete,
		SettingIP,
		SettingPort
	};
private:
	ModeBase& _preWindow;

	State _state;
	bool _analogFlag;

	/*選択しているメニュー項番*/
	int _selectIndex;
	/*最大項番*/
	int _selectMAX;

	int _settingIPIndex;
	std::array<int,4> _keyInputHandlesIP;
	int _keyInputHandlePort;
	int _netTCPHandle;
	int _netUDPRecieveHandle,_netUDPSendHandle;
	IPDATA _ip;
	int _port;
	int _dataLength;
	int _connectError;

	int _font;
};
