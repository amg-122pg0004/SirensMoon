/*****************************************************************//**
 * \file   InputManager.h
 * \brief	���͏�Ԃ��擾�A�ێ�����
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#pragma once
#include <vector>
#include <string>

class InputManager{

	public:
		
		InputManager();//<�R���X�g���N�^

		/**@brief �g�p����e�L�[�ɂ��ăC���v�b�g��Ԃ��m�F���ĕۑ� */
		void InputUpdate();
		
		/**
		* @brief ����̃L�[�̓��͏�Ԃ��m�F����
		*
		* \param actionname �m�F�������L�[�A�N�V�����̖��O
		* \param keystate �m�F�������L�[�̏�� 'h'�ŉ��������Ă��邩�H't'�ŉ������u�Ԃ��H
		* \return ���͂������true
		*/
		bool CheckInput(const std::string actionname,const char keystate,int playernum);
#ifdef _DEBUG
		void Render();
#endif 

		

private:
	/*�P�L�[���Ƃ̓��͏��*/
	struct KeyInfo {
		std::string ActionName;	//<�e�{�^���ɑΉ������A�N�V�����̖��O
		int KeyName;			//<�A�N�V�����ɕR�t���Ă���{�^���̖��O
		bool Hold;				//<���͂��ꑱ���Ă����true��Ԃ�
		bool Trigger;			//<���͂��ꂽ�u�Ԃ̂�true��Ԃ�
		int PadNo;				//<���͂����R���g���[���[�̔ԍ�
	};

	/*�Q�[�����Ŏg�p����e�A�N�V�����ɂ��Ă̓��͏�Ԃ�ۑ�����*/
	std::vector<KeyInfo> KeyState;
};
