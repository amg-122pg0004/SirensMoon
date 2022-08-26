#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class BigGenerator :public Gimmick {
public:
	BigGenerator(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::BigGenerator; }
	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos);
	bool GetSignalActive() { return _active; };
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
	void UpdateCollsiion();
	void SetPattern(int pattern,std::vector<bool> signal);
private:

	bool CheckHitBullet();

	bool _active;//<��������^�C�~���O

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
};