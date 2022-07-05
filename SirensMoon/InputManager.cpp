/*****************************************************************//**
 * \file   InputManager.cpp
 * \brief  ���͏�Ԃ��擾�A�ێ�����
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#include <DxLib.h>
#include "InputManager.h"
#include <vector>
#include <string>
#include <sstream>

InputManager::InputManager() {
	KeyState= {
			{"UP",PAD_INPUT_UP,false,false,0},
			{"DOWN",PAD_INPUT_DOWN,false,false,0},
			{"LEFT",PAD_INPUT_LEFT,false,false,0},
			{"RIGHT",PAD_INPUT_RIGHT,false,false,0},
			{"ACTION",PAD_INPUT_10,false,false,0},
			{"UP",PAD_INPUT_UP,false,false,1},
			{"DOWN",PAD_INPUT_DOWN,false,false,1},
			{"LEFT",PAD_INPUT_LEFT,false,false,1},
			{"RIGHT",PAD_INPUT_RIGHT,false,false,1},
			{"ACTION",PAD_INPUT_1,false,false,1},
	};
}

/**@brief �g�p����e�L�[�ɂ��ăC���v�b�g��Ԃ��m�F���ĕۑ� */
void InputManager::InputUpdate() {

	for (auto&& key : KeyState) {
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
}

/**
 * @brief ����̃L�[�̓��͏�Ԃ��m�F����
 * 
 * \param actionname �m�F�������L�[�A�N�V�����̖��O
 * \param keystate �m�F�������L�[�̏�� 'h'�ŉ��������Ă��邩�H't'�ŉ������u�Ԃ��H
 * \return ���͂������true
 */
bool InputManager::CheckInput(const std::string actionname, const char keystate,int playernum) {
	for (auto&& key : KeyState)
		if (key.ActionName == actionname && key.PadNo==playernum) 
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
	return false;
}

void InputManager::Render() {
	std::stringstream ss;
	for (auto&& key : KeyState) {
		ss << key.ActionName <<" "<< key.KeyName <<" " << key.Hold <<" "<< key.Trigger << "\n";
	}

	DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
}
