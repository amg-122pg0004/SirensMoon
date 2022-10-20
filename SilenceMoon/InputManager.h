/*****************************************************************//**
 * \file   InputManager.h
 * \brief	���͏�Ԃ��擾�A�ێ�����
 *
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#pragma once
#include "Math.h"
#include <vector>
#include <string>
#include <array>

#include<algorithm>
#include <unordered_map>
#include "NetDataStructs.h"

class InputManager {

public:

	InputManager();//<�R���X�g���N�^
	void InitConfig();

	/**@brief �g�p����e�L�[�ɂ��ăC���v�b�g��Ԃ��m�F���ĕۑ� */
	void InputUpdate();
	void InputUpdatePlayer0(int inputType);
	void InputUpdatePlayer0(int key,Vector2 analog);
	void InputUpdatePlayer1(int inputType);
	void InputUpdatePlayer1(int key, Vector2 analog);
	/**
	* @brief ����̃L�[�̓��͏�Ԃ��m�F����
	*
	* \param actionname �m�F�������L�[�A�N�V�����̖��O
	* \param keystate �m�F�������L�[�̏�� 'h'�ŉ��������Ă��邩�H't'�ŉ������u�Ԃ��H
	* \return ���͂������true
	*/
	bool CheckInput(const std::string actionname, const char keystate, int playernum);

	/**
	* @brief �A�i���O�X�e�B�b�N�̓��͏�Ԃ��m�F����
	*
	* \param playernum ���ڂ̃R���g���[���[��
	* \return ���͏�Ԃ����̂܂ܕԂ�
	*/
	Vector2 CheckAnalogInput(const int playernum);

	void ChangeControllerNo();
	void SetOnline(int playerNo) { _online = playerNo; }

#ifdef _DEBUG
	void Render();
#endif 
	std::vector<int> GetPlayer0Key() { return _player0Key; }
	std::vector<int> GetPlayer1Key() { return _player1Key; }
	std::vector<Vector2> GetPlayer0Analog() { return _player0Analog; }
	std::vector<Vector2> GetPlayer1Analog() { return _player1Analog; }
	
	int GetOnlinePlayer() { return _online; };
private:
	/*�L�[�Ή��ݒ�*/
	std::unordered_map<std::string, int> _player0Config, _player1Config;
	/*�L�[�̓��͏�Ԃ��ߋ��t���[���܂߂ĕۑ��i�ŐV��back()�j*/
	std::vector<int> _player0Key, _player1Key;
	/*�A�i���O�X�e�B�b�N�̓��͏�Ԃ��ߋ��t���[���܂߂ĕۑ��ŐV��back())*/
	std::vector<Vector2> _player0Analog, _player1Analog;

	/*�R���g���[���[�����ւ���t���O*/
	bool _changeFlag;

	/*�ڑ����̃R���g���[���[�̐�*/
	int _connectNumber;

	int _online;
	// 2�i���o�͂���֐�
	std::string ToBin(int a, int keta);
};