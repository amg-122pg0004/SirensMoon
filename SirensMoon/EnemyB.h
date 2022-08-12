#pragma once
#include "Enemy.h"

class EnemyB:public Enemy{
public:
	EnemyB(Game& game, ModeGame& mode, ObjectDataStructs::EnemyBData enemydata, EnemyGenerator::EnemyPattern pattern);

	void Update() override;

	Type GetType()override { return Type::Enemy; }

	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);
private:
	
	/*向いている方向を示す配列番号*/
	int _index;
	/*経過フレーム*/
	int _elapsed;

	ObjectDataStructs::EnemyBData _data;
};
