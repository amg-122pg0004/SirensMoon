#pragma once
//#include "EnemyB.h"
//
//class EnemyB:public Actor{
//public:
//	EnemyB(Game& game, ModeGame& mode, ObjectDataStructs::EnemyBData enemydata, EnemyGenerator::EnemyGrData grdata);
//
//	void Update();
//
//	/*���E������X�V*/
//	void  SightUpdate();
//	/*���E���Ƀv���C���[�����邩����*/
//	bool CheckDetection();
//
//	/*�e�A�v���C���[�ƐG��Ă��邩�m�F����*/
//	virtual void CheckDamage();
//	/*�v���C���[�֐ڋ߂���*/
//	void MoveToPlayer();
//	/*�v���C���[�Ƀ_���[�W��^����*/
//	void ApplyDamage();
//	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;
//
//	void UpdateCollision();
//	void AnimationUpdate();
//
//private:
//	/*���E����*/
//	class BoxSight {
//	public:
//		Vector2 pos1, pos2, pos3, pos4;//<�G���_�����O���E�A�����E
//	};
//
//	void Init();
//
//
//	/*�����Ă������*/
//	Vector2 _dir;
//
//	BoxSight _sightPos;
//	/*��̈ʒu*/
//	Vector2 _eyePos;
//
//	/*�ǐՃt���O*/
//	bool _chase;
//	/*���E�͈�*/
//	const int _sight_H, _sight_W;
//	/*���E�͈͓��ɂ����t���[����*/
//	int _detectionFrame;
//	/*�Ō�ɔ�����������*/
//	Actor* _lastDetection;
//
//
//	ObjectDataStructs::EnemyBData _data;
//
//	/*Enemy�����_�������p�^�[��*/
//	std::vector<int> _generatedEnemy;
//	/*Enemy���摜*/
//	std::map<EnemyGenerator::EnemyDirection, int> _cg_top;
//	std::map<EnemyGenerator::EnemyDirection, int> _cg_mid;
//	std::map<EnemyGenerator::EnemyDirection, int> _cg_top2;
//	std::map<EnemyGenerator::EnemyDirection, int> _cg_bot;
//
//	EnemyGenerator::EnemyDirection _cg_direction;
//	int _animeNo;//<�A�j���[�V�����̕\���ԍ�
//};
