#pragma once
#include "Actor.h"
#include "ObjectDataStructs.h"
#include <vector>

class BossGimmickController:public Actor{
public:
	BossGimmickController(Game& game,ModeGame& mode, ObjectDataStructs::BossGimmickControllerData data);
	std::vector<int> GetPattern() { return _pattern; }

	Type GetType()override { return Type::BossGimmickController; }

	void Update() override;

	/*�{�X�̐���*/
	void BossSpawn();
	/*�t�F�C�Y2�ڍs���O*/
	void PrePhase2();
	/*�t�F�C�Y2�ڍs��*/
	void Phase2();
	/*�p�^�[���̐���*/
	void GeneratePattern();
	/*�p�^�[�����̔z�z*/
	void DistributePattern();

	/*���d�@���N�����ꂽ�ۂɌĂ΂��֐�*/
	void RecieveStartGenerator(int no);
	

private:
	int _index;//<���d�@�i�s��
	std::vector<int> _pattern;//<�p�^�[��

	bool _phase1;
	bool _phase2;
	bool _readyRailgun;

	/*�e�M�~�b�N��ID*/
	int _gun;
	int _teleport;
	std::vector<int> _servers;
	std::vector<int> _generators;

	static const std::vector<bool> GetSignal(int index) {
		static const std::vector<std::vector<bool>> signal = {
			{1,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,},
			{1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,0,0,},
			{1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,0},
			{1,0,1,0,1,0,1,0,1,0,0,0,}
		};
		return signal[index];
	}
};