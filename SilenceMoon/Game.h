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
#include "Network.h"

constexpr int screen_W{ 1920 };//<ウィンドウの解像度：横
constexpr int screen_H{ 1080 };//<ウィンドウの解像度：縦
constexpr int screen_Depth{ 32 };//<ウィンドウの色数(bit)
constexpr int splitscreen_W{ screen_W / 2 - 30 };

class Game {

public:
	enum class Progress {
		StartUp1,
		StartUp2,
		StartUp3,
		Intro,
		StartMenu,
		Stage1,
		Stage1Clear,
		Stage2,
		Stage2Clear,
		Stage3,
		Stage3Clear,
		Credit
	};

	Game();//<Gameコンストラクタ
	void Input();//<入力の取得
	void Update();//<計算、更新
	void Render();//<描画更新
	void Debug();//<デバッグ用表示
	void RestartMode();
	void NextMode();
	void GameOver();
	/**
	 * @brief インプットマネージャーの取得
	 * @return インプットマネージャーの参照を返す
	 */
	inline  auto GetInputManager() { return _inputManager; }

	inline int GetFrameCount() { return _frameCount; }

	std::unique_ptr<ModeServer>& GetModeServer() { return _modeServer; }

	int GetFont22() { return _font22; }
	int GetFont26() { return _font26; }
	Progress GetProgress() { return _progress; }
	void PlayStartUp1();
	void PlayStartUp2();
	void PlayStartUp3();
	void PlayIntro();
	void PlayStartMenu();
	void PlayStartMenuSkipMovie();
	void PlayStage1();
	void PlayStage1Clear();
	void PlayStage2();
	void PlayStage2Clear();
	void PlayStage3();
	void PlayStage3Clear();
	void PlayCredit();

	void StartNetwork();

	std::unique_ptr<Network>& GetNetwork() { return _network; }
	void SetOnlineNo(int no) { _online = no; }
	int GetOnlineNo() { return _online ; }
private:
	int _font22, _font26;
	std::shared_ptr<InputManager> _inputManager;
	std::unique_ptr<ModeServer> _modeServer;
	std::unique_ptr<Network> _network;
	int _frameCount;
	bool _debug;
	Progress _progress;
	int _online;
};