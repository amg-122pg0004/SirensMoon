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

		virtual void Move();
		bool IsHitActor();
		virtual void Action();
		void PlayFootSteps();
		void UpdateCollision();
		void TakeDamage();
		void Heal();
		void TakeAmmo();

		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

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

	protected:
		std::shared_ptr<InputManager> _inputManager;

		Vector2 _dir;//<キャラの向き
		Vector2 _lastDir;//最後に向いたキャラの向き
		Vector2 _speed;//移動の速さ
		double _speedMax;//移動の最大速
		bool _movable;

		int _playerNum;//<プレイヤーの番号(0なら左プレイヤー、1なら右プレイヤー）
		int _hp;//<体力

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