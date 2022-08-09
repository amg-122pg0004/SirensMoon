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

InputManager::InputManager() :_changeFlag{0} {
	_keyState= {
			{"UP",PAD_INPUT_UP,false,false,false,0},
			{"DOWN",PAD_INPUT_DOWN,false,false,false,0},
			{"LEFT",PAD_INPUT_LEFT,false,false,false,0},
			{"RIGHT",PAD_INPUT_RIGHT,false,false,false,0},
			{"ACTION",PAD_INPUT_1,false,false,false,0},
			{"PAUSE",PAD_INPUT_12,false,false,false,0},
			{"CHANGE",PAD_INPUT_13,false,false,false,0},
			{"ACCESS",PAD_INPUT_3,false,false,false,0},
			{"DEBUG",PAD_INPUT_11,false,false,false,0},
			{"BLIND",PAD_INPUT_8,false,false,false,0},
			{"BLIND2",PAD_INPUT_7,false,false,false,0},
			{"BULLET1",PAD_INPUT_5,false,false,false,0},
			{"BULLET2",PAD_INPUT_6,false,false,false,0},
			{"UP",PAD_INPUT_UP,false,false,false,1},
			{"DOWN",PAD_INPUT_DOWN,false,false,false,1},
			{"LEFT",PAD_INPUT_LEFT,false,false,false,1},
			{"RIGHT",PAD_INPUT_RIGHT,false,false,false,1},
			{"ACTION",PAD_INPUT_1,false,false,false,1},
			{"PAUSE",PAD_INPUT_12,false,false,false,1},
			{"CHANGE",PAD_INPUT_13,false,false,false,1},
			{"ACCESS",PAD_INPUT_3,false,false,false,1},
			{"DEBUG",PAD_INPUT_11,false,false,false,1},
			{"BLIND",PAD_INPUT_8,false,false,false,1},
			{"BLIND2",PAD_INPUT_7,false,false,false,1},
			{"BULLET1",PAD_INPUT_5,false,false,false,0},
			{"BULLET2",PAD_INPUT_6,false,false,false,0},
	};

	_analogState = {
		{{0,0},0},
		{{0,0},1}
	};
}

/**@brief �g�p����e�L�[�ɂ��ăC���v�b�g��Ԃ��m�F���ĕۑ� */
void InputManager::InputUpdate() {
	int padno0=-1,padno1=-1;
	if (_changeFlag) {
		padno0 = DX_INPUT_PAD2;
		padno1 = DX_INPUT_KEY_PAD1;
	}
	else {
		padno0 = DX_INPUT_KEY_PAD1;
		padno1 = DX_INPUT_PAD2;
	}
	
	for (auto&& key :_keyState) {
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
			else if(key.Hold==true){
				key.Release = true;
				key.Hold = false;
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
			}else if (key.Hold == true) {
				key.Release = true;
				key.Hold = false;
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
		int InputX, InputY;
		switch (analog.PadNo) {
		case 0:
			GetJoypadAnalogInput(&InputX, &InputY, padno0);
			analog.Value = { static_cast<double>(InputX),static_cast<double>(InputY) };
			continue;
		case 1:
			GetJoypadAnalogInput(&InputX, &InputY, padno1);
			analog.Value = { static_cast<double>(InputX),static_cast<double>(InputY) };
			continue;
		default:
			break;
		}
	}
}

/**
 * @brief ����̃L�[�̓��͏�Ԃ��m�F����
 * 
 * \param actionname �m�F�������L�[�A�N�V�����̖��O
 * \param keystate �m�F�������L�[�̏�� 'h'�ŉ��������Ă��邩�H't'�ŉ������u�Ԃ��H'r'�ŗ������u�Ԃ��H
 * \return ���͂������true
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

void InputManager::Render() {
	
	std::stringstream ss;
	for (auto&& key : _keyState) {
		ss << key.ActionName <<" "<< key.KeyName <<" " << key.Hold <<" "<< key.Trigger<<" "<<key.Release << "\n";
	}
	for (auto&& analog : _analogState) {
		ss  <<"�A�i���O�X�e�B�b�N�v���C���["<<analog.PadNo<<" "<< analog.Value.x <<" "<<analog.Value.y << "\n";
	}

	DrawString(50, 100, ss.str().c_str(), GetColor(255, 255, 255));
	
}

void InputManager::ChangeControllerNo(){

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
