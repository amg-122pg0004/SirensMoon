#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class BigGenerator :public Gimmick {
public:
	BigGenerator(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data,std::vector<bool> signal);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::BigGenerator; }
	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos);
	bool GetSignalActive() { return _active; };
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

private:
	bool _active;//<��������^�C�~���O

	/*�P���\���t���[����*/
	int _span;
	/*���݂̕\���t���[����*/
	int _elapsed;

	/*���ݕ\�����̃V�O�i������*/
	int _index;
	/*Generator���d�l����V�O�i���p�^�[��*/
	std::vector<bool> _signal;
};
