#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class BigServer:public Gimmick{
public:
	BigServer(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data,std::vector<int> pattern);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::BigServer; }
	void Update()override;
	void StandardRender(Vector2 window_pos,Vector2 camera_pos);
	bool GetAccessible() { return _accessible; }

private:
	std::vector<int> _pattern;
	bool _accessible;
};