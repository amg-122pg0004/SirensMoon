/*****************************************************************//**
 * \file   EnemyGenerator.h
 * \brief  �G�������_���������邽�߂̃N���X�ł��B
 *
 * \author �y�������Y
 * \date   August 2022
 *********************************************************************/
#pragma once
#include <vector>
#include <memory>

class EnemyGenerator {
public:
	struct EnemyPattern
	{
		int head;
		int body;
		int foot;
	};

	EnemyGenerator(EnemyPattern maxnum );
	~EnemyGenerator();
	void Init();
	/*�z�񂩂�EnemyPattern�����ԂɕԂ�*/
	EnemyPattern GetEnemyPattern();
	/*�z�񂩂�EnemyPattern�����ԂɕԂ��A�Ԃ����l�͔z�񂩂�폜*/
	EnemyPattern GetEnemyVIPPattern();
	/*�z�񂩂�EnemyPattern�����ԂɕԂ�*/
	int* GetEnemyALLPatternArray() ;
	/*_enemyAllPattern���Z�b�g*/
	void SetEnemyALLPatternArray(int data[255]);

private:
	/*�e���ő剽�ʂ葶�݂��邩*/
	EnemyPattern _numberOfTypes;
	/*�S�ʂ�̑g�ݍ��킹*/
	std::vector<EnemyPattern> _enemyAllPattern;
	/*�Ō�ɉ��Ԗڂ̃f�[�^���Q�Ƃ������H*/
	int _lastGet;
	int _arrayData[255];
};