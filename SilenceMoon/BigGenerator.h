/*****************************************************************//**
 * \file   BigGenerator.h
 * \brief  �{�X�M�~�b�N���쓮�����邽�߂�
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class BossGimmickController;

class BigGenerator :public Gimmick {
public:
	BigGenerator(Game& game, ModeGame& mode, BigGeneratorData data, BossGimmickController& controller);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::BigGenerator; }
	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos);
	bool GetSignalActive() { return _flash; };
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
	void UpdateCollsiion();
	void SetPattern(int pattern,std::vector<bool> signal);
	bool GetAccessible() { return _accessible; }
private:

	bool CheckHitBullet();

	bool _flash;//<��������^�C�~���O

	/*�P���\���t���[����*/
	int _span;
	/*���݂̕\���t���[����*/
	int _elapsed;

	/*���ݕ\�����̓_�ō���*/
	int _index;
	/*Generator���g�p���郉�C�g�_�Ńp�^�[��*/
	std::vector<bool> _signal;
	/*�p�^�[������*/
	int _pattern;

	/*�R���g���[���[�̎Q��*/
	BossGimmickController& _controller;

	int _cg_active, _cg_passive;

	AABB _accessArea;
	bool _accessible;
};