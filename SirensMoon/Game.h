/*****************************************************************//**
 * \file   Game.h
 * \brief  プロセスを管理します。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <DxLib.h>
#include <memory>
#include <vector>
#include "InputManager.h"
#include "MapChip.h"
#include "Math.h"
#include "SplitWindow.h"
#include "ActorServer.h"
#include "Player.h"

class Camera;
class MapChip;
class SplitWindow;
class ActorServer;


constexpr int screen_W{1600};//<ウィンドウの解像度：横
constexpr int screen_H{900};//<ウィンドウの解像度：縦
constexpr int screen_Depth{32};//<ウィンドウの色数(bit)

class Game {

	public:
		Game();//<Gameコンストラクタ
		void Input();//<入力の取得
		void Update();//<計算、更新
		void Render();//<描画更新
		/**
		 * @brief インプットマネージャーの取得
		 * @return インプットマネージャーの参照を返す
		 */
		inline std::shared_ptr<InputManager>& GetInputManager() { return _inputManager; }
		inline std::unique_ptr<MapChip>& GetMapChip() { return _mapChip; }

		//ActorServer &GetActorServer() { return _actorServer; }

	private:
		std::shared_ptr<InputManager> _inputManager;
		std::unique_ptr<MapChip>_mapChip;
		std::vector<std::unique_ptr<SplitWindow>>_splitWindow;

	protected:
		ActorServer _actorServer;
};
