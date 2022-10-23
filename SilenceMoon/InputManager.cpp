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
	AddMinusFrameDummyData();
	InitConfig();//追加版
}

/**@brief 使用する各キーについてインプット状態を確認して保存 */
void InputManager::InputUpdate() {
	if (_player0Key.size() > 0) {
		_player0Key.erase(_player0Key.begin());
	}
	if (_player1Key.size() > 0) {
		_player1Key.erase(_player1Key.begin());
	}
	if (_player0Analog.size() > 0) {
		_player0Analog.erase(_player0Analog.begin());
	}
	if (_player1Analog.size() > 0) {
		_player1Analog.erase(_player1Analog.begin());
	}
	if (_recieveInputFrame.size() > 0) {
		_recieveInputFrame.erase(_recieveInputFrame.begin());
	}
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
	int currentKey{ 0 }, oldKey{ 0 };

	if (key.size() > 0) {
			currentKey = *(key.end() - 1);
	}

	if (key.size() > 1) {
			oldKey = *(key.end() - 2);
	}

	auto inputKey = config[actionname];
	int trg, release;
	switch (keystate) {
	case 'h':
		return currentKey & inputKey;
	case 't':
		trg = (currentKey ^ oldKey) & currentKey;
		return trg & inputKey;
	case 'r':
		release = (currentKey ^ oldKey) & oldKey;
		return release & inputKey;
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
	for (auto&& key : _player0Key) {
		ss << ToBin(key, 32) << "\n";
	}

	DrawFormatString(100, 100, GetColor(255, 255, 255), ss.str().c_str());
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

	_player0Key = { 0 };
	_player1Key = { 0 };


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
		_player0Config = xboxInputConfig;
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

	if (_player0Key.size() > 10) {
		_player0Key.erase(_player0Key.begin());
	}
	if (_player0Analog.size() > 10) {
		_player0Analog.erase(_player0Analog.begin());
	}
}

void InputManager::InputUpdatePlayer1(int inputType) {
	_player1Key.push_back(GetJoypadInputState(inputType));
	int x, y;
	GetJoypadAnalogInput(&x, &y, inputType);
	_player1Analog.push_back({ static_cast<double>(x),static_cast<double>(y) });
	if (_player1Key.size() > 10) {
		_player1Key.erase(_player1Key.begin());
	}
	if (_player1Analog.size() > 10) {
		_player1Analog.erase(_player1Analog.begin());
	}
}
void InputManager::InputUpdatePlayer0(int key, Vector2 analog, int frame) {
	_player0Key.push_back(key);
	_player0Analog.push_back(analog);
	_recieveInputFrame.push_back(frame);

	if (_player0Key.size() > 10) {
		_player0Key.erase(_player0Key.begin());
	}
	if (_player0Analog.size() > 10) {
		_player0Analog.erase(_player0Analog.begin());
	}
	if (_recieveInputFrame.size() > 10) {
		_recieveInputFrame.erase(_recieveInputFrame.begin());
	}
}

void InputManager::InputUpdatePlayer1(int key, Vector2 analog, int frame) {
	_player1Key.push_back(key);
	_player1Analog.push_back(analog);
	_recieveInputFrame.push_back(frame);

	if (_player1Key.size() > 10) {
		_player1Key.erase(_player1Key.begin());
	}
	if (_player1Analog.size() > 10) {
		_player1Analog.erase(_player1Analog.begin());
	}
	if (_recieveInputFrame.size() > 10) {
		_recieveInputFrame.erase(_recieveInputFrame.begin());
	}
}

bool InputManager::CheckHaveKeyData() {
	if (_online == 0) {
		if (_player1Key.size() >= 2) {
			return true;
		}
	}
	if (_online == 2) {
		if (_player1Key.size() >= 2) {
			return true;
		}
	}
	return false;
}

void InputManager::AddMinusFrameDummyData() {
	int key{ 0 };
	_player0Key.push_back(key);
	_player1Key.push_back(key);
	Vector2 analog{ 0,0 };
	_player0Analog.push_back(analog);
	_player1Analog.push_back(analog);
	_recieveInputFrame.push_back(-1);
	_recieveInputFrame.push_back(-2);
}

std::string InputManager::ToBin(int a, int keta) {
	std::string s = "";
	do {
		if (a % 2 == 0) {
			s = "0" + s;
		}
		else {
			s = "1" + s;
		}
		a /= 2;
		keta--;
	} while (a > 0 || keta > 0);
	return s;
}
