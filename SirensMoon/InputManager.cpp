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

InputManager::InputManager() {
	_keyState= {
			{"UP",PAD_INPUT_UP,false,false,0},
			{"DOWN",PAD_INPUT_DOWN,false,false,0},
			{"LEFT",PAD_INPUT_LEFT,false,false,0},
			{"RIGHT",PAD_INPUT_RIGHT,false,false,0},
			{"ACTION",PAD_INPUT_1,false,false,0},
			{"UP",PAD_INPUT_UP,false,false,1},
			{"DOWN",PAD_INPUT_DOWN,false,false,1},
			{"LEFT",PAD_INPUT_LEFT,false,false,1},
			{"RIGHT",PAD_INPUT_RIGHT,false,false,1},
			{"ACTION",PAD_INPUT_1,false,false,1},
	};

	_analogState = {
		{{0,0},0},
		{{0,0},1}
	};
}

/**@brief 使用する各キーについてインプット状態を確認して保存 */
void InputManager::InputUpdate() {

	for (auto&& key :_keyState) {
		switch (key.PadNo) {
		case 0:
			if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & key.KeyName) {
				if (key.Hold == false) {
					key.Trigger = true;
				}
				else {
					key.Trigger = false;
				}
				key.Hold = true;
				continue;
			}
			break;
		case 1:
			if (GetJoypadInputState(DX_INPUT_PAD2) & key.KeyName) {
				if (key.Hold == false) {
					key.Trigger = true;
				}
				else {
					key.Trigger = false;
				}
				key.Hold = true;
				continue;
			}
			break;
		default:
			break;
		}

		key.Trigger = false;
		key.Hold = false;
	}

	for (auto&& analog : _analogState) {
		int InputX, InputY;
		switch (analog.PadNo) {
		case 0:
			GetJoypadAnalogInput(&InputX, &InputY, DX_INPUT_KEY_PAD1);
			analog.Value = { static_cast<double>(InputX),static_cast<double>(InputY) };
			continue;
		case 1:
			GetJoypadAnalogInput(&InputX, &InputY, DX_INPUT_PAD2);
			analog.Value = { static_cast<double>(InputX),static_cast<double>(InputY) };
			continue;
		default:
			break;
		}
	}
}

/**
 * @brief 特定のキーの入力状態を確認する
 * 
 * \param actionname 確認したいキーアクションの名前
 * \param keystate 確認したいキーの状態 'h'で押し続けているか？'t'で押した瞬間か？
 * \return 入力があればtrue
 */
bool InputManager::CheckInput(const std::string actionname, const char keystate,int playernum) {
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

void InputManager::Render() {
	std::stringstream ss;
	for (auto&& key : _keyState) {
		ss << key.ActionName <<" "<< key.KeyName <<" " << key.Hold <<" "<< key.Trigger << "\n";
	}
	for (auto&& analog : _analogState) {
		ss  <<"アナログスティックプレイヤー"<<analog.PadNo<<" "<< analog.Value.x <<" "<<analog.Value.y << "\n";
	}

	DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
}
