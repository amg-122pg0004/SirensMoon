#pragma once

//#include <DxLib.h>
//#include "Actor.h"
//#include "Game.h"
//#include <vector>
//
//class Enemy :public Actor {
//	public :
//		Enemy(Game& game,Vector2 setpos);
//
//		/**
//		 * @brief �s���̌���A�X�V
//		 * 
//		 */
//		void Update();
//
//		/**
//		 * @brief �O���t�B�b�N�̕\��
//		 * 
//		 * \param stagenum �����_�����O����X�e�[�W�ԍ�
//		 * \param window_pos ������ʂ̈ʒu
//		 * \param camera_pos �J�����̍��W
//		 */
//		void Render(int stagenum, Vector2 window_pos, Vector2 camera_pos);
//
//		/*�ړ�������W��z��ɃZ�b�g����*/
//		void SetPatrolPoints();
//
//		/*�z�񂩂玟�Ɍ��������W���擾*/
//		void GetNextPoints();
//
//		/**
//		 * @brief �������Ă�����W�ɓ������������肷��
//		 * 
//		 * \return ����������True��Ԃ�
//		 */
//		bool CheckReachPoint();
//
//	private:
//
//		/*�����X�s�[�h*/
//		int _speed;
//
//		/*�������Ă�����W*/
//		Vector2 _nextPos;
//
//		
//
//		std::vector<Vector2> _patrolPoints;
//
//		/*CG��*/
//		std::vector<int> _cg;
//		/*CG�ύX�p�Ɏg�p���Ă���X�e�[�g*/
//		enum class State {
//			UP,DOWN,LEFT,RIGHT
//		};
//
//		State _state;
//};