#pragma once
#include <vector>
class ModeGame;
class Actor;

class BossGimmickController{
public:
	BossGimmickController(ModeGame& mode);
	std::vector<int> GetPattern() { return _pattern; }


	/*�p�^�[���̐���*/
	void GeneratePattern();
	/*�p�^�[�����̔z�z*/
	void DistributePattern();

	/*���d�@���N�����ꂽ�ۂɌĂ΂��֐�*/
	void RecieveStartGenerator(int no);
	

private:
	int _index;//<���d�@�i�s��
	std::vector<int> _pattern;//<�p�^�[��

	ModeGame& _mode;

	/*�e�M�~�b�N�̃|�C���^*/
	Actor* _gun;
	std::vector<Actor*> _servers;
	std::vector<Actor*> _generators;

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