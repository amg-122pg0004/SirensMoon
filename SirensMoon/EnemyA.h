#pragma once

#include "Enemy.h"
class Game;
class ModeBase;
class ModeGame;

class EnemyA :public Enemy {
public:
	EnemyA(Game& game, ModeGame& mode, ObjectDataStructs::EnemyData data, EnemyGenerator::EnemyPattern pattern);
	/**
	 * @brief �s���̌���A�X�V
	 *
	 */
	Type GetType()override { return Type::Enemy; }
	virtual void Update()override;

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

	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

protected:
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
	/*�ҋ@�t���[��*/
	int _waitFrame, _elapseFrame;
};