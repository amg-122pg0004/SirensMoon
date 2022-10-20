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

InputManager::InputManager() :_changeFlag{ 0 }, _online{ -1 } {

	InitConfig();//�ǉ���
}

/**@brief �g�p����e�L�[�ɂ��ăC���v�b�g��Ԃ��m�F���ĕۑ� */
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
 * @brief ����̃L�[�̓��͏�Ԃ��m�F����
 *
 * \param actionname �m�F�������L�[�A�N�V�����̖��O
 * \param keystate �m�F�������L�[�̏�� 'h'�ŉ��������Ă��邩�H't'�ŉ������u�Ԃ��H'r'�ŗ������u�Ԃ��H
 * \return ���͂������true
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
		{ "ACTION",PAD_INPUT_3	},
		{ "PAUSE",PAD_INPUT_8	},
		{ "CHANGE",PAD_INPUT_10	},
		{ "ACCESS",PAD_INPUT_1	},
		{ "DEBUG",PAD_INPUT_7	},
		{ "BULLET1",PAD_INPUT_5	},
		{ "BULLET2",PAD_INPUT_6	},
		/*
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
		*/
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
void InputManager::InputUpdatePlayer0(int key, Vector2 analog) {
	_player0Key.push_back(key);
	_player0Analog.push_back(analog);

	if (_player0Key.size() > 60) {
		_player0Key.erase(_player0Key.begin());
	}
	if (_player0Analog.size() > 60) {
		_player0Analog.erase(_player0Analog.begin());
	}
}

void InputManager::InputUpdatePlayer1(int key, Vector2 analog) {
	_player1Key.push_back(key);
	_player1Analog.push_back(analog);

	if (_player1Key.size() > 60) {
		_player1Key.erase(_player1Key.begin());
	}
	if (_player1Analog.size() > 60) {
		_player1Analog.erase(_player1Analog.begin());
	}
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
