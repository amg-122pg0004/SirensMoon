#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Game;
class ModeGame;

class ScreenPump :public Gimmick {
public:
	ScreenPump(Game& game, ModeGame& mode, ObjectDataStructs::MineData data);

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::Mine; }

	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

private:
	AABB _detectionArea;
	int _dir;
	int _range;
};
