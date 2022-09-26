#pragma once
#include "Enemy.h"

class EnemyB:public Enemy{
public:
	EnemyB(Game& game, ModeGame& mode, EnemyBData enemydata, EnemyGenerator::EnemyPattern pattern);

	void Update() override;

	Type GetType()override { return Type::Enemy; }

	void Debug(Vector2 window_pos, Vector2 camera_pos);
private:
	
	/*�����Ă�������������z��ԍ�*/
	int _index;
	/*�o�߃t���[��*/
	int _elapsed;

	EnemyBData _data;
};