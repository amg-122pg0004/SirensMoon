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

	Init();
}

void InputManager::Init() {
	_keyState.clear();
	_connectNumber = GetJoypadNum();
	std::vector<KeyInfo> keys;
	for (int i = 0; i < 2; ++i) {
		/*InputState 1はDX_INPUT_PAD1,2はDX_INPUT_PAD2,*/
		if (CheckJoypadXInput(i + 1)) {
			/*XInput用のキーコンフィグ*/
			keys = {
			{ "UP",PAD_INPUT_UP,false,false,false,i },
			{ "DOWN",PAD_INPUT_DOWN,false,false,false,i },
			{ "LEFT",PAD_INPUT_LEFT,false,false,false,i },
			{ "RIGHT",PAD_INPUT_RIGHT,false,false,false,i },
			{ "ACTION",PAD_INPUT_3,false,false,false,i },
			{ "PAUSE",PAD_INPUT_8,false,false,false,i },
			{ "CHANGE",PAD_INPUT_10,false,false,false,i },
			{ "ACCESS",PAD_INPUT_1,false,false,false,i },
			{ "DEBUG",PAD_INPUT_7,false,false,false,i },
			{ "BULLET1",PAD_INPUT_5,false,false,false,i },
			{ "BULLET2",PAD_INPUT_6,false,false,false,i }
			};
		}
		else {
			/*DirectInput用のキーコンフィグ*/
			keys = {
			{"UP", PAD_INPUT_UP, false, false, false, i},
			{ "DOWN",PAD_INPUT_DOWN,false,false,false,i },
			{ "LEFT",PAD_INPUT_LEFT,false,false,false,i },
			{ "RIGHT",PAD_INPUT_RIGHT,false,false,false,i },
			{ "ACTION",PAD_INPUT_1,false,false,false,i },
			{ "PAUSE",PAD_INPUT_12,false,false,false,i },
			{ "CHANGE",PAD_INPUT_13,false,false,false,i },
			{ "ACCESS",PAD_INPUT_3,false,false,false,i },
			{ "DEBUG",PAD_INPUT_11,false,false,false,i },
			{ "BULLET1",PAD_INPUT_5,false,false,false,i },
			{ "BULLET2",PAD_INPUT_6,false,false,false,i }
			};
		}
		_keyState.insert(_keyState.end(), keys.begin(), keys.end());
	}
	_analogState = {
		{{0,0},0},
		{{0,0},1}
	};
}

/**@brief 使用する各キーについてインプット状態を確認して保存 */
void InputManager::InputUpdate() {
	if (_connectNumber != GetJoypadNum()) {
		Init();
	}

	int padno0 = -1, padno1 = -1;
	if (_changeFlag) {
		padno0 = DX_INPUT_PAD2;
		padno1 = DX_INPUT_KEY_PAD1;
	}
	else {
		padno0 = DX_INPUT_KEY_PAD1;
		padno1 = DX_INPUT_PAD2;
	}
	if (_online != -1) {
		padno0 = DX_INPUT_KEY_PAD1;
		padno1 = DX_INPUT_KEY_PAD1;
	}
	for (auto&& key : _keyState) {
		if (_online == 0 && key.PadNo == 1) {
			continue;
		}
		if (_online == 1 && key.PadNo == 0) {
			continue;
		}
		switch (key.PadNo) {
		case 0:
			if (GetJoypadInputState(padno0) & key.KeyName) {
				if (key.Hold == false) {
					key.Trigger = true;
				}
				else {
					key.Trigger = false;
				}
				key.Hold = true;

				continue;
			}
			else if (key.Hold == true) {
				key.Release = true;
				key.Hold = false;
				key.Trigger = false;
				continue;
			}
			break;
		case 1:
			if (GetJoypadInputState(padno1) & key.KeyName) {
				if (key.Hold == false) {
					key.Trigger = true;
				}
				else {
					key.Trigger = false;
				}
				key.Hold = true;
				continue;
			}
			else if (key.Hold == true) {
				key.Release = true;
				key.Hold = false;
				key.Trigger = false;
				continue;
			}
			break;
		default:
			break;
		}
		key.Trigger = false;
		key.Hold = false;
		key.Release = false;
	}

	for (auto&& analog : _analogState) {
		int InputX{0}, InputY{0};
		if (analog.PadNo == 0) {
			GetJoypadAnalogInput(&InputX, &InputY, padno0);
		}
		else if (analog.PadNo == 1) {
			GetJoypadAnalogInput(&InputX, &InputY, padno1);
		}
		analog.Value = { static_cast<double>(InputX),static_cast<double>(InputY) };
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
	for (auto&& key : _keyState) {
		if (key.ActionName == actionname && key.PadNo == playernum)
		{
			switch (keystate)
			{
			case 'h':
				return key.Hold;
				break;
			case 't':
				return key.Trigger;
				break;
			case 'r':
				return key.Release;
			default:
				return false;
				break;
			}
		}
	}
	return false;
}

Vector2 InputManager::CheckAnalogInput(const int playernum) {

	for (auto&& analog : _analogState) {
		if (analog.PadNo == playernum) {
			return analog.Value;
			break;
		}
	}
	return { 0,0 };
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
	for (auto&& key : _keyState) {
		key.Trigger = false;
		key.Hold = false;
		key.Release = false;
	}
}

void InputManager::SetUDPData(std::array<int, 14> rawData) {
	int setplayer{ -1 };
	if (_online == 0) {
		setplayer = 1;
	}
	else if (_online == 1) {
		setplayer = 0;
	}
	_analogState[setplayer].Value.x = rawData[1];
	_analogState[setplayer].Value.y = rawData[2];
	int i = 2;
	for (auto&& key : _keyState) {
		if (key.PadNo != setplayer) {
			continue;
	}
		++i;
		if (rawData[i] == 1) {
			if (key.Hold == false) {
				key.Trigger = true;
			}
			else {
				key.Trigger = false;
			}
			key.Hold = true;
		}
		else {
			if (key.Hold == true) {
				key.Release = true;
			}
			else {
				key.Release = false;
			}
			key.Hold = false;
		}
	}


}
