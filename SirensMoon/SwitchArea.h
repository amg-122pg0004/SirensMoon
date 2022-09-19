#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class SwitchArea :public Gimmick {
public:
	SwitchArea(Game& game, ModeGame& mode, SwitchAreaData data);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::SwitchArea; }
	void Update()override;
	void LinkGimmickActivate(bool flag);
	void Debug(Vector2 window_pos, Vector2 camera_pos);

private:
	std::vector<int> _linkGimmiks;
	AABB _accessArea;
	bool _reverse;
};
