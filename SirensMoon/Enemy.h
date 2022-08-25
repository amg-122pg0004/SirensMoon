/*****************************************************************//**
 * \file   Enemy.h
 * \brief  基本敵キャラクター
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "Actor.h"
#include <vector>
#include <map>
#include <set>
#include "EnemyGenerator.h"
#include "ObjectDataStructs.h"


class Game;
class ModeGame;

class Enemy :public Actor {
public:
	/*視界判定*/
	class BoxSight {
	public:
		Vector2 pos1, pos2, pos3, pos4;//<敵視点から手前左右、奥左右
	};

	Enemy(Game& game, ModeGame& mode, EnemyGenerator::EnemyPattern pattern);
	virtual void Init();
	/**
	 * @brief 行動の決定、更新
	 *
	 */
	Type GetType()override { return Type::Enemy; }
	bool GetChaseFlag() { return _chase; }
	Actor* GetLastDetection() { return _lastDetection; }
	BoxSight GetSightPosition() { return _sightPos; }


	virtual void Update()override;

	/*グラフィックハンドルをセットする*/
	void SetGrHandle(EnemyGenerator::EnemyPattern);

	/**
	 * @brief グラフィックの表示
	 *
	 * \param stagenum レンダリングするステージ番号
	 * \param window_pos 分割画面の位置
	 * \param camera_pos カメラの座標
	 */
	virtual void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;

	/*視界判定を更新*/
	void  SightUpdate();
	/*視界内にプレイヤーが居るか判定*/
	bool CheckDetection();

	bool CheckVisualLine();

	/*弾、プレイヤーと触れているか確認する*/
	virtual void CheckDamage();
	/*ダメージを受ける*/
	virtual void TakeDamage(Type);
	/*プレイヤーへ接近する*/
	void MoveToPlayer();
	/*プレイヤーにダメージを与える*/
	void ApplyDamage();
	virtual void Debug(Vector2 window_pos, Vector2 camera_pos) override;

	void UpdateCollision();
	void AnimationUpdate();

	Vector2 CheckRoomPosition() override;

protected:
	enum class EnemyDirection {
		Down,
		DownLeft,
		Left,
		UpLeft,
		Up,
		UpRight,
		Right,
		DownRight
	};


	void SetDirection();

	/*初期位置*/
	Vector2 _initPos;
	/*歩くスピード*/
	int _speed;
	/*向いている方向*/
	Vector2 _dir;

	BoxSight _sightPos;
	/*眼の位置*/
	Vector2 _eyePos;

	/*追跡フラグ*/
	bool _chase;
	/*視界範囲*/
	const int _sight_H, _sight_W;
	/*視界範囲内にいたフレーム数*/
	int _detectionFrame;
	/*最後に発見した物体*/
	Actor* _lastDetection;
	/*視線上のグリッド*/
	std::set<std::pair<int, int>> _eyelineGrids;
	/*Enemyランダム生成パターン*/
	EnemyGenerator::EnemyPattern _pattern;
	/*Enemy仮画像*/
	std::map<EnemyDirection, int> _cg_top;
	std::map<EnemyDirection, int> _cg_mid;
	std::map<EnemyDirection, int> _cg_top2;
	std::map<EnemyDirection, int> _cg_bot;

	EnemyDirection _cg_direction;
	int _animeNo;//<アニメーションの表示番号
};