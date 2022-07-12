#pragma once

//#include <DxLib.h>
//#include "Actor.h"
//#include "Game.h"
//#include <vector>
//
//class Enemy :public Actor {
//	public :
//		Enemy(Game& game,Vector2 setpos);
//
//		/**
//		 * @brief 行動の決定、更新
//		 * 
//		 */
//		void Update();
//
//		/**
//		 * @brief グラフィックの表示
//		 * 
//		 * \param stagenum レンダリングするステージ番号
//		 * \param window_pos 分割画面の位置
//		 * \param camera_pos カメラの座標
//		 */
//		void Render(int stagenum, Vector2 window_pos, Vector2 camera_pos);
//
//		/*移動する座標を配列にセットする*/
//		void SetPatrolPoints();
//
//		/*配列から次に向かう座標を取得*/
//		void GetNextPoints();
//
//		/**
//		 * @brief 向かっている座標に到着したか判定する
//		 * 
//		 * \return 到着したらTrueを返す
//		 */
//		bool CheckReachPoint();
//
//	private:
//
//		/*歩くスピード*/
//		int _speed;
//
//		/*向かっている座標*/
//		Vector2 _nextPos;
//
//		
//
//		std::vector<Vector2> _patrolPoints;
//
//		/*CGを*/
//		std::vector<int> _cg;
//		/*CG変更用に使用しているステート*/
//		enum class State {
//			UP,DOWN,LEFT,RIGHT
//		};
//
//		State _state;
//};