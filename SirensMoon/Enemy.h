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

		/*���E������X�V*/
		void  SightUpdate();
		/*���E���Ƀv���C���[�����邩����*/
		bool CheckDetection();
		/**
		 * \brief ����AB��CD���������Ă��邩
		 * 
		 * \param a�@����AB�̎n�_
		 * \param b�@����AB�̏I�_
		 * \param c�@����CD�̎n�_
		 * \param d�@����CD�̎n�_
		 * \return �@�������Ă����True
		 */
		bool IsCrossed(Vector2 a,Vector2 b,Vector2 c,Vector2 d);

		void CheckDamage();
		void ApplyDamage();
		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;

		void UpdateCollision();
		void AnimationUpdate();

	private:
		/*�����ʒu*/
		Vector2 _initPos;
		/*�����X�s�[�h*/
		int _speed;
		/*�����Ă������*/
		Vector2 _dir;

		/*���E����*/
		class BoxSight {
		public:
			Vector2 pos1, pos2, pos3, pos4;//<�G���_�����O���E�A�����E
		};

		BoxSight _sightPos;
		/*��̈ʒu*/
		Vector2 _eyePos;

		/*���E�͈�*/
		const int _sight_H, _sight_W;
		/*���E�͈͓��ɂ����t���[����*/
		int _detectionFrame;
		/*�Ō�ɔ�����������*/
		Actor* _lastDetection;

		/*���񃋁[�g��ID*/
		int _patrolID;
		/*����p�^�[��*/
		bool _patrolMode;
		/*����̕���*/
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
		std::vector<int> _cg2;
		std::vector<int> _cg_red1, _cg_red2, _cg_red3;
		std::vector<int> _cg_blue1, _cg_blue2, _cg_blue3;
		std::vector<int> _cg_green1, _cg_green2, _cg_green3;

		int _animeNo;//<�A�j���[�V�����̕\���ԍ�
};