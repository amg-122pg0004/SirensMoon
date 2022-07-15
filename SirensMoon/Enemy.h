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
#include "MapChip.h"

class Game;
class ModeBase;

class Enemy :public Actor {
	public :
		Enemy(Game& game, ModeBase& mode,MapChips::EnemyData enemy);
		/**
		 * @brief 行動の決定、更新
		 * 
		 */
		Type GetType()override { return Type::Enemy; }
		void Update()override;

		/**
		 * @brief グラフィックの表示
		 * 
		 * \param stagenum レンダリングするステージ番号
		 * \param window_pos 分割画面の位置
		 * \param camera_pos カメラの座標
		 */
		void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

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

	private:
		/*初期位置*/
		Vector2 _initPos;
		/*歩くスピード*/
		int _speed;

		/*巡回ルートのID*/
		int _patrolID;
		/*巡回パターン*/
		bool _patrolMode;
		int _patrolFlag;
		/*向かっている座標の配列番号*/
		int _patrolIndex;
		/*向かっている座標*/
		Vector2 _nextPos;
		/*巡回する座標リスト*/
		std::vector<Vector2> _patrolPoints;
		/*座標リストの長さ*/
		int _patrolLength;

		/*Enemy仮画像*/
		int _cg;
};