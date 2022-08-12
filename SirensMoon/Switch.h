#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Switch :public Gimmick{
public:

	Switch(Game& game, ModeGame& mode, ObjectDataStructs::SwitchData data);

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::Switch; }

	void Update()override;
	void LinkGimmickActivate(bool flag);
	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);

private:
	AABB _accessArea;
	std::vector<int> _linkGimmiks;
};