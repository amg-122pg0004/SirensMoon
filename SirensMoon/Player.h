/*****************************************************************//**
 * \file   Player.h
 * \brief  プレイヤーキャラ
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include "Actor.h"
#include "InputManager.h"
#include "Game.h"
#include "Math.h"


class Player :public Actor {
	public:
		Player(Game& game,int playernum);
		void Update() override ;
		void StandardRender(int stageNum,Vector2 window_pos,Vector2 camera_pos) override ;
		void ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;

		Type GetType() override { return Type::Player; }
		int GetPlayerNum() { return _playerNum; }

		void Move();
		void CheckStress();
		void GunShoot();
		void OpenMap();

		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

	private:
		std::shared_ptr<InputManager> _inputManager;

		Vector2 _dir;//<キャラの向き
		Vector2 _lastDir;//最後に向いたキャラの向き
		Vector2 _speed;//移動の速さ
		double _speedMax;//移動の最大速度
		int _playerNum;//<プレイヤーの番号(0なら左プレイヤー、1なら右プレイヤー）

		float _stress;//<ストレスゲージ
		float _stressSpeed;//<ストレスゲージが変化する速度

		/*キャラクターの画像ハンドル*/
		int _cg_up;
		int _cg_side;
		int _cg_down;
		int _cg_recon;

};