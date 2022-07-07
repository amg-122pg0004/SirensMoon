#pragma once
#include <DxLib.h>
#include <vector>
#include "Game.h"
#include "Math.h"

class SplitWindow;

class Darkness {
	public:
		Darkness(Game& game,SplitWindow& splitwindow);
		/*マスクデータの作成*/
		int MakeDarkness();
		/*マスクデータの更新*/
		void Update(Vector2 window_pos, Vector2 camera_pos);
		/*マスクデータの削除*/
		void DeleteDarkness();

	private:
		Game& _game;
		SplitWindow& _splitWindow;

		int _cg;//マスク用画像取得用
		int _alphaHandle;
};