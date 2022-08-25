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
#include <map>
#include <set>
#include "EnemyGenerator.h"
#include "ObjectDataStructs.h"


class Game;
class ModeGame;

class Enemy :public Actor {
public:
	/*���E����*/
	class BoxSight {
	public:
		Vector2 pos1, pos2, pos3, pos4;//<�G���_�����O���E�A�����E
	};

	Enemy(Game& game, ModeGame& mode, EnemyGenerator::EnemyPattern pattern);
	virtual void Init();
	/**
	 * @brief �s���̌���A�X�V
	 *
	 */
	Type GetType()override { return Type::Enemy; }
	bool GetChaseFlag() { return _chase; }
	Actor* GetLastDetection() { return _lastDetection; }
	BoxSight GetSightPosition() { return _sightPos; }


	virtual void Update()override;

	/*�O���t�B�b�N�n���h�����Z�b�g����*/
	void SetGrHandle(EnemyGenerator::EnemyPattern);

	/**
	 * @brief �O���t�B�b�N�̕\��
	 *
	 * \param stagenum �����_�����O����X�e�[�W�ԍ�
	 * \param window_pos ������ʂ̈ʒu
	 * \param camera_pos �J�����̍��W
	 */
	virtual void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;

	/*���E������X�V*/
	void  SightUpdate();
	/*���E���Ƀv���C���[�����邩����*/
	bool CheckDetection();

	bool CheckVisualLine();

	/*�e�A�v���C���[�ƐG��Ă��邩�m�F����*/
	virtual void CheckDamage();
	/*�_���[�W���󂯂�*/
	virtual void TakeDamage(Type);
	/*�v���C���[�֐ڋ߂���*/
	void MoveToPlayer();
	/*�v���C���[�Ƀ_���[�W��^����*/
	void ApplyDamage();
	virtual void Debug(Vector2 window_pos, Vector2 camera_pos) override;

	void UpdateCollision();
	void AnimationUpdate();

	Vector2 CheckRoomPosition() override;

protected:
	enum class EnemyDirection {
		Down,
		DownLeft,
		Left,
		UpLeft,
		Up,
		UpRight,
		Right,
		DownRight
	};


	void SetDirection();

	/*�����ʒu*/
	Vector2 _initPos;
	/*�����X�s�[�h*/
	int _speed;
	/*�����Ă������*/
	Vector2 _dir;

	BoxSight _sightPos;
	/*��̈ʒu*/
	Vector2 _eyePos;

	/*�ǐՃt���O*/
	bool _chase;
	/*���E�͈�*/
	const int _sight_H, _sight_W;
	/*���E�͈͓��ɂ����t���[����*/
	int _detectionFrame;
	/*�Ō�ɔ�����������*/
	Actor* _lastDetection;
	/*������̃O���b�h*/
	std::set<std::pair<int, int>> _eyelineGrids;
	/*Enemy�����_�������p�^�[��*/
	EnemyGenerator::EnemyPattern _pattern;
	/*Enemy���摜*/
	std::map<EnemyDirection, int> _cg_top;
	std::map<EnemyDirection, int> _cg_mid;
	std::map<EnemyDirection, int> _cg_top2;
	std::map<EnemyDirection, int> _cg_bot;

	EnemyDirection _cg_direction;
	int _animeNo;//<�A�j���[�V�����̕\���ԍ�
};