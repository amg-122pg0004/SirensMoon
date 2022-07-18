/*****************************************************************//**
 * \file   Game.h
 * \brief  プロセスを管理します。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <memory>
#include <vector>
#include "InputManager.h"
#include "ModeServer.h"


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

		inline int GetFrameCount() { return _frameCount; }


	private:
		std::shared_ptr<InputManager> _inputManager;
		std::unique_ptr<ModeServer> _modeServer;
		int _frameCount;
};