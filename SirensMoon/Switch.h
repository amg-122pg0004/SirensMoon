#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Switch :public Gimmick{
public:

	Switch(Game& game, ModeGame& mode, ObjectDataStructs::SwitchData data);

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::Switch; }
	bool GetAccessible1() { return _accessible1; }
	bool GetAccessible2() { return _accessible2; }
	void Update()override;
	void LinkGimmickActivate(bool flag);
	void Debug(Vector2 window_pos, Vector2 camera_pos);

private:
	int _cg2,_cg3;
	AABB _accessArea;
	bool _accessible1;
	bool _accessible2;
	std::vector<int> _linkGimmiks;

	std::vector<Vector2> _linkGimmickPositions;
};
