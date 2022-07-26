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
class ModeGame;

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

		/*視界判定を更新*/
		void  SightUpdate();
		/*視界内にプレイヤーが居るか判定*/
		bool CheckDetection();
		/**
		 * \brief 線分ABとCDが交差しているか
		 * 
		 * \param a　線分ABの始点
		 * \param b　線分ABの終点
		 * \param c　線分CDの始点
		 * \param d　線分CDの始点
		 * \return 　交差していればTrue
		 */
		bool IsCrossed(Vector2 a,Vector2 b,Vector2 c,Vector2 d);

		void CheckDamage();
		void ApplyDamage();
		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;

		void UpdateCollision();
		void AnimationUpdate();

		void GenerateEnemy();
		bool CheckWantedEnemy(ModeGame&);

	private:
		/*初期位置*/
		Vector2 _initPos;
		/*歩くスピード*/
		int _speed;
		/*向いている方向*/
		Vector2 _dir;

		/*視界判定*/
		class BoxSight {
		public:
			Vector2 pos1, pos2, pos3, pos4;//<敵視点から手前左右、奥左右
		};

		BoxSight _sightPos;
		/*眼の位置*/
		Vector2 _eyePos;

		/*視界範囲*/
		const int _sight_H, _sight_W;
		/*視界範囲内にいたフレーム数*/
		int _detectionFrame;
		/*最後に発見した物体*/
		Actor* _lastDetection;

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


		/*Enemyランダム生成パターン*/
		std::vector<int> _generatedEnemy;
		/*Enemy仮画像*/
		std::vector<int> _cg_top;
		std::vector<int> _cg_mid;
		std::vector<int> _cg_bot;

		int _animeNo;//<アニメーションの表示番号
};