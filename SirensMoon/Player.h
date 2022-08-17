/*****************************************************************//**
 * \file   Player.h
 * \brief  プレイヤーキャラ
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "Actor.h"
#include "InputManager.h"
#include "Math.h"
#include <map>
#include <memory>


class Game;
class ModeGame;

class Player :public Actor {
	public:
		Player(Game& game,ModeGame& base,int playernum);
		void Update() override ;
		virtual void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos ) override;
		void UpdateCamera();
		void Init();

		virtual Actor::Type GetType() override { return Type::Player; }
		int GetPlayerNum() { return _playerNum; }
		Vector2 GetDirection() { return _lastDir; }
		int GetCharge() { return _charge; }
		int GetHP() { return _hp; }
		int GetAmmo() { return _bullet; }

		virtual void Move();
		bool IsHitActor();
		/*プレイヤー固有のアクション*/
		virtual void Action();
		/*足音の再生*/
		void PlayFootSteps();
		/*プレイヤー同士が重なっている場合の処理*/
		void PlayerOverlap();
		/*コリジョンボックスの位置更新*/
		void UpdateCollision();
		/*ダメージを判定に触れているかの確認*/
		void CheckDamage();
		/*被ダメージ時の処理*/
		void TakeDamage(Actor::Type);
		void Heal();
		void TakeAmmo();
		void ChangePosition(Vector2 pos);
		void Checkteleport();

		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;



	protected:

		/*グラフィック用状態*/
		enum class PlayerState {
			Wait,
			Walk,
			Run,
			Set,
			Shoot
		};
		/*グラフィック用方向*/
		enum class PlayerDirection {
			Up,
			Down,
			Left,
			Right,
		};

		std::shared_ptr<InputManager> _inputManager;

		Vector2 _dir;//<キャラの向き
		Vector2 _lastDir;//最後に向いたキャラの向き
		Vector2 _speed;//移動の速さ
		double _speedMax;//最大速度
		double _accelerationRatio;//入力値をノーマライズした値の乗算値を加速する
		double _friction;//速度減衰に使用する値
		bool _movable;

		int _playerNum;//<プレイヤーの番号(0なら左プレイヤー、1なら右プレイヤー）
		int _hp,_hpMAX;//<体力

		int _invincibleTime;

		/*射撃関係*/
		int _bullet;//残りの弾数
		int _charge;//チャージ
		int _cooldown;//クールダウン

		/*キャラクターの画像ハンドル*/
		std::map <std::pair<PlayerState, PlayerDirection>, std::vector<int >> _cg;

		int _animNo;

		/*ライトの光画像*/
		int _cg_light;

		bool _init;

		PlayerState _state;
		PlayerDirection _direction;

};