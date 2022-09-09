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

	Player(Game& game, ModeGame& base, int playernum);
	void Update() override;
	virtual void StandardRender(Vector2 window_pos, Vector2 camera_pos) override;
	void UpdateCamera();
	void Init();

	virtual Actor::Type GetType() override { return Type::Player; }
	int GetPlayerNum() { return _playerNum; }
	Vector2 GetDirection() { return _lastDir; }
	PlayerDirection GetGrDirection() { return _direction; }
	int GetHP() { return _hp; }

	virtual void Move();
	virtual void AnimUpdate();
	bool IsHitActor();
	/*プレイヤー固有のアクション*/
	virtual void Action();
	/*プレイヤー同士が重なっている場合の処理*/
	void PlayerOverlap();
	/*コリジョンボックスの位置更新*/
	void UpdateCollision();
	/*ダメージを判定に触れているかの確認*/
	void CheckDamage();
	/*被ダメージ時の処理*/
	void TakeDamage(Actor::Type);
	void Heal();
	void ChangePosition(Vector2 pos);
	bool Checkteleport();
	virtual void TeleportEvent();
	void ChangeMovable(bool flag) { _movable = flag; }

	/*ハイドフラグの確認*/
	void UpdateHide();
	bool GetHideFlag() { return _hide; }
	bool SetHideFlag();

	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

	protected:

		std::shared_ptr<InputManager> _inputManager;

		Vector2 _dir;//<キャラの向き
		Vector2 _lastDir;//最後に向いたキャラの向き
		Vector2 _speed;//移動の速さ
		double _speedMax;//最大速度
		double _accelerationRatio;//入力値をノーマライズした値の乗算値を加速する
		double _friction;//速度減衰に使用する値
		bool _movable;//<True時のみ移動可能
		bool _stageMovable;//<True時画面外への移動を制限する

		bool _hide;//<true時敵から見つからない
		int _hideTime;

		int _playerNum;//<プレイヤーの番号(0なら左プレイヤー、1なら右プレイヤー）
		int _hp,_hpMAX;//<体力

		int _invincibleTime;//<無敵時間

		/*キャラクターの画像ハンドル*/
		std::map <std::pair<PlayerState, PlayerDirection>, std::vector<int >> _cg;

		int _animNo;
		bool _visible;
		/*ライトの光画像*/
		int _cg_light;

		bool _init;

		PlayerState _state;
		PlayerDirection _direction;

		Vector2 _teleportPosition;
		int _teleportDelay;
};