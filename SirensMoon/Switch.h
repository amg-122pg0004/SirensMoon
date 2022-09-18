#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Camera;

class Switch :public Gimmick{
public:

	Switch(Game& game, ModeGame& mode, SwitchData data);

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::Switch; }
	bool GetAccessible1() { return _accessible1; }
	bool GetAccessible2() { return _accessible2; }
	void Update()override;
	bool LinkGimmickActivate(bool flag);
	void Debug(Vector2 window_pos, Vector2 camera_pos);

	void FirstActivateEvent(int eventPlayer);

private:
	void RayToLinks();
	int _firstActivate;//<�@0�@=�@����N���C�x���g���s�O�@1=�v���C���[A�����s 2=�v���C���[B�����s
	int _cg2,_cg3;
	AABB _accessArea;
	bool _accessible1;
	bool _accessible2;
	std::vector<int> _linkGimmiks;

	/*�����N���Ă��镡���̃M�~�b�N�̂����A�ォ��_projectionNumber�̐��܂ł̃M�~�b�N�ɃG�t�F�N�g���΂�*/
	int _projectionNumber;
	std::vector<Vector2> _linkGimmickPositions;
	bool _stopRay;
	int _timer;
};
