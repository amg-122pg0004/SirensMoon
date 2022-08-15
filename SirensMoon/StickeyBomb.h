#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Game;
class ModeGame;

class StickyBomb :public Gimmick {
public:
	StickyBomb(Game& game, ModeGame& mode, ObjectDataStructs::StickyBombData data);

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::StickyBomb; }

	void Update()override;
	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

private:

	/*くっついているプレイヤー*/
	Actor* _player;
	/*感知範囲*/
	AABB _detectionArea;
	/*解除アクション範囲*/
	AABB _accessArea;
	/*爆破までの時間*/
	int _timer;

	
};




