/*****************************************************************//**
 * \file   SoundServer.h
 * \brief  �����̓ǂݍ��݁A�폜���s���N���X�ł��B
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once

#include <unordered_map>

class SoundServer {
public:
	static void Init();//<_mapGraph�̏�����
	static void Release();//<ClearGraph�Ăяo��

	static void ClearSounds();//<_mapGraph�f�[�^�̑S�폜

	/**
	 * \brief _mapGraph�̃L�[����
	 *
	 * \param filename ��������L�[��
	 * \return �L�[�ɑΉ������l��Ԃ�
	 */
	static int Find(std::string filename);

	/**
	 * \brief �ǂݍ��ݍς̃t�@�C���o�Ȃ����map�ɓo�^
	 *
	 * \param filename �ǂݍ��ރt�@�C����
	 * \return �ǂݍ��񂾒l�A�ǂݍ��ݍς݂Ȃ�-1��Ԃ�
	 */
	static int LoadSound(std::string key, std::string filename);
	
	static void StopALLSound();

private:
	static std::unordered_map<std::string, int> _mapSounds;
};