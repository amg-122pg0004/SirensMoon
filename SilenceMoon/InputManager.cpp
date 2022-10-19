/*****************************************************************//**
 * \file   InputManager.cpp
 * \brief  入力状態を取得、保持する
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#include <DxLib.h>
#include "InputManager.h"
#include <vector>
#include <string>
#include <sstream>

InputManager::InputManager() :_changeFlag{ 0 }, _online{ -1 } {

	InitConfig();//追加版
}

/**@brief 使用する各キーについてインプット状態を確認して保存 */
void InputManager::InputUpdate() {
	if (_online == -1) {
		if (_changeFlag) {
			InputUpdatePlayer0(DX_INPUT_PAD2);
			InputUpdatePlayer1(DX_INPUT_PAD1);
		}
		else {
			InputUpdatePlayer0(DX_INPUT_PAD1);
			InputUpdatePlayer1(DX_INPUT_PAD2);
		}
	}
	else if (_online == 0) {
		InputUpdatePlayer0(DX_INPUT_PAD1);
	}
	else if (_online == 1) {
		InputUpdatePlayer1(DX_INPUT_PAD1);
	}

}

/**
 * @brief 特定のキーの入力状態を確認する
 *
 * \param actionname 確認したいキーアクションの名前
 * \param keystate 確認したいキーの状態 'h'で押し続けているか？'t'で押した瞬間か？'r'で離した瞬間か？
 * \return 入力があればtrue
 */
bool InputManager::CheckInput(const std::string actionname, const char keystate, int playernum) {
	std::unordered_map<std::string, int> config;
	std::vector<int> key;
	if (playernum == 0) {
		config = _player0Config;
		key = _player0Key;
	}
	else if (playernum == 1) {
		config = _player1Config;
		key = _player1Key;
	}
	switch (keystate) {
	case 'h':
		return key.back() & config[actionname];
	case 't':
		return (key.back() & config[actionname]) ^ (key.back() - 1 & config[actionname]) & (key.back() & config[actionname]);
	case 'r':
		return (key.back() & config[actionname]) ^ (key.back() - 1 & config[actionname]) & (key.back() - 1 & config[actionname]);;
	default:
		return false;
	}
}

Vector2 InputManager::CheckAnalogInput(const int playernum) {
	if (playernum == 0) {
		return _player0Analog.back();
	}
	else if (playernum == 1) {
		return _player1Analog.back();
	}
}
#ifdef _DEBUG
void InputManager::Render() {

	std::stringstream ss;
	for (auto&& key : _keyState) {
		ss << key.ActionName << " " << key.KeyName << " " << key.Hold << " " << key.Trigger << " " << key.Release << " PadNo." << key.PadNo << "\n";
	}
	for (auto&& analog : _analogState) {
		ss << "アナログスティックプレイヤー" << analog.PadNo << " " << analog.Value.x << " " << analog.Value.y << "\n";
	}
	ss << "接続コントローラー数" << _connectNumber << "\n";
	GUID buff;
	auto test = GetJoypadGUID(DX_INPUT_PAD1, &buff);
	ss << "接続GUID" << GetJoypadGUID(DX_INPUT_PAD1, &buff) << "\n";
	DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
}
#endif 
void InputManager::ChangeControllerNo() {

	if (_changeFlag) {
		_changeFlag = 0;
	}
	else {
		_changeFlag = 1;
	}
	auto tmp = _player0Config;
	_player0Config = _player1Config;
	_player1Config = tmp;

	auto tmp2 =_player0Key;
	_player0Key = _player1Key;
	_player1Key = tmp2;


}

void InputManager::SetUDPData(std::array<int, 14> rawData) {

}

void InputManager::InitConfig() {
	std::unordered_map<std::string, int> xboxInputConfig = {
			{ "UP",PAD_INPUT_UP		},
			{ "DOWN",PAD_INPUT_DOWN	},
			{ "LEFT",PAD_INPUT_LEFT	},
			{ "RIGHT",PAD_INPUT_RIGHT},
			{ "ACTION",PAD_INPUT_3	},
			{ "PAUSE",PAD_INPUT_8	},
			{ "CHANGE",PAD_INPUT_10	},
			{ "ACCESS",PAD_INPUT_1	},
			{ "DEBUG",PAD_INPUT_7	},
			{ "BULLET1",PAD_INPUT_5	},
			{ "BULLET2",PAD_INPUT_6	},
	};
	std::unordered_map<std::string, int> directInputConfig = {
		{ "UP",PAD_INPUT_UP		},
		{ "DOWN",PAD_INPUT_DOWN	},
		{ "LEFT",PAD_INPUT_LEFT	},
		{ "RIGHT",PAD_INPUT_RIGHT},
		{ "ACTION",PAD_INPUT_1	},
		{ "PAUSE",PAD_INPUT_8	},
		{ "CHANGE",PAD_INPUT_10	},
		{ "ACCESS",PAD_INPUT_3	},
		{ "DEBUG",PAD_INPUT_7	},
		{ "BULLET1",PAD_INPUT_5	},
		{ "BULLET2",PAD_INPUT_6	},
	};
	if (CheckJoypadXInput(0)) {
		_player0Config=xboxInputConfig;
	}
	else {
		_player0Config = directInputConfig;
	}
	if (CheckJoypadXInput(1)) {
		_player1Config = xboxInputConfig;
	}
	else {
		_player1Config = directInputConfig;
	}
}

void InputManager::InputUpdatePlayer0(int inputType) {
	_player0Key.push_back(GetJoypadInputState(inputType));
	int x, y;
	GetJoypadAnalogInput(&x, &y, inputType);
	_player0Analog.push_back({ static_cast<double>(x),static_cast<double>(y) });

	if (_player0Key.size() > 60) {
		_player0Key.erase(_player0Key.begin());
	}
	if (_player0Analog.size() > 60) {
		_player0Analog.erase(_player0Analog.begin());
	}
}

void InputManager::InputUpdatePlayer1(int inputType) {
	_player1Key.push_back(GetJoypadInputState(inputType));
	int x, y;
	GetJoypadAnalogInput(&x, &y, inputType);
	_player1Analog.push_back({ static_cast<double>(x),static_cast<double>(y) });
	if (_player1Key.size() > 60) {
		_player1Key.erase(_player1Key.begin());
	}
	if (_player1Analog.size() > 60) {
		_player1Analog.erase(_player1Analog.begin());
	}
}
