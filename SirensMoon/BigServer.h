#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class BigServer:public Gimmick{
public:
	BigServer(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::BigServer; }
	void Update()override;
	void StandardRender(Vector2 window_pos,Vector2 camera_pos);
	bool GetAccessible() { return _accessible; }
	void SetPattern(std::vector<int> pattern);

private:
	std::vector<int> _pattern;
	AABB _accessArea;
	bool _accessible;
};