#pragma once

#include "Enemy.h"
class Game;
class ModeBase;
class ModeGame;

class EnemyA :public Enemy {
public:
	EnemyA(Game& game, ModeGame& mode, ObjectDataStructs::EnemyData data, EnemyGenerator::EnemyPattern pattern);
	/**
	 * @brief 行動の決定、更新
	 *
	 */
	Type GetType()override { return Type::Enemy; }
	virtual void Update()override;

	/*次に向かう座標へ進む*/
	void MoveNextPoint();

	/*移動する座標を配列にセットする。コンストラクタで呼ぶ*/
	void SetPatrolPoints();

	/*配列から次に向かう座標を取得*/
	void GetNextPoints();

	/**
	 * @brief 向かっている座標に到着したか判定する
	 *
	 * \return 到着したらTrueを返す
	 */
	bool CheckReachPoint();

	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

protected:
	/*巡回ルートのID*/
	int _patrolID;
	/*巡回パターン*/
	bool _patrolMode;
	/*巡回の方向*/
	int _patrolFlag;
	/*向かっている座標の配列番号*/
	int _patrolIndex;
	/*向かっている座標*/
	Vector2 _nextPos;
	/*巡回する座標リスト*/
	std::vector<Vector2> _patrolPoints;
	/*座標リストの長さ*/
	int _patrolLength;
	/*待機フレーム*/
	int _waitFrame, _elapseFrame;
};