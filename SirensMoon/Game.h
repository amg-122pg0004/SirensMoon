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
#include "Math.h"
#include "InputManager.h"
#include "SplitWindow.h"
#include "ActorServer.h"
#include "Player.h"
#include "MapChip.h"
#include "Camera.h"
#include "ReconPlayer.h"

constexpr int screen_W{1920};//<ウィンドウの解像度：横
constexpr int screen_H{1080};//<ウィンドウの解像度：縦
constexpr int screen_Depth{32};//<ウィンドウの色数(bit)

class Game {

	public:
		Game();//<Gameコンストラクタ
		void Input();//<入力の取得
		void Update();//<計算、更新
		void Render();//<描画更新
		void Debug();//<デバッグ用表示

		/**
		 * @brief インプットマネージャーの取得
		 * @return インプットマネージャーの参照を返す
		 */
		inline  auto GetInputManager() { return _inputManager; }
		inline  auto& GetMapChips() { return _mapChips; }
		inline  auto& GetActorServer() { return _actorServer; }
		inline auto& GetSplitWindow() { return _splitWindow; }

	private:
		std::shared_ptr<InputManager> _inputManager;
		std::unique_ptr<MapChips>_mapChips;
		std::vector<std::unique_ptr<SplitWindow>>_splitWindow;

	protected:
		std::unique_ptr <ActorServer> _actorServer;
};