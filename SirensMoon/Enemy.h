/*****************************************************************//**
 * \file   Enemy.h
 * \brief  ��{�G�L�����N�^�[
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "Actor.h"
#include <vector>
#include "MapChip.h"

class Game;
class ModeBase;

class Enemy :public Actor {
	public :
		Enemy(Game& game, ModeBase& mode,MapChips::EnemyData enemy);
		/**
		 * @brief �s���̌���A�X�V
		 * 
		 */
		Type GetType()override { return Type::Enemy; }
		void Update()override;

		/**
		 * @brief �O���t�B�b�N�̕\��
		 * 
		 * \param stagenum �����_�����O����X�e�[�W�ԍ�
		 * \param window_pos ������ʂ̈ʒu
		 * \param camera_pos �J�����̍��W
		 */
		void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

		/*���Ɍ��������W�֐i��*/
		void MoveNextPoint();

		/*�ړ�������W��z��ɃZ�b�g����B�R���X�g���N�^�ŌĂ�*/
		void SetPatrolPoints();

		/*�z�񂩂玟�Ɍ��������W���擾*/
		void GetNextPoints();

		/**
		 * @brief �������Ă�����W�ɓ������������肷��
		 * 
		 * \return ����������True��Ԃ�
		 */
		bool CheckReachPoint();

	private:
		/*�����ʒu*/
		Vector2 _initPos;
		/*�����X�s�[�h*/
		int _speed;

		/*���񃋁[�g��ID*/
		int _patrolID;
		/*����p�^�[��*/
		bool _patrolMode;
		int _patrolFlag;
		/*�������Ă�����W�̔z��ԍ�*/
		int _patrolIndex;
		/*�������Ă�����W*/
		Vector2 _nextPos;
		/*���񂷂���W���X�g*/
		std::vector<Vector2> _patrolPoints;
		/*���W���X�g�̒���*/
		int _patrolLength;

		/*Enemy���摜*/
		int _cg;
};