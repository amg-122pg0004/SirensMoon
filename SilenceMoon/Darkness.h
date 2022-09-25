/*****************************************************************//**
 * \file   Darkness.h
 * \brief  暗闇表現用クラス
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <vector>
#include "Math.h"

class Game;
class ModeGame;
class SplitWindow;

class Darkness {
	public:
		Darkness(Game& game, ModeGame& mode, SplitWindow& splitwindow);
		/*マスクデータの作成*/
		int MakeDarkness();
		/*マスクデータの更新*/
		void Update(Vector2 window_pos, Vector2 camera_pos);
		/*マスクデータの削除*/
		void DeleteDarkness();

	private:
		Game& _game;
		ModeGame& _mode;
		SplitWindow& _splitWindow;

		int _cg;//マスク用画像取得用
		int _cg2;
		int _alphaHandle;

};