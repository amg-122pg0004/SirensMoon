#pragma once
#include <DxLib.h>
#include <vector>
#include "Math.h"

class Game;
class ModeBase;
class SplitWindow;

class Darkness {
	public:
		Darkness(Game& game, ModeBase& mode, SplitWindow& splitwindow);
		/*マスクデータの作成*/
		int MakeDarkness();
		/*マスクデータの更新*/
		void Update(Vector2 window_pos, Vector2 camera_pos);
		/*マスクデータの削除*/
		void DeleteDarkness();

	private:
		Game& _game;
		ModeBase& _mode;
		SplitWindow& _splitWindow;

		int _cg;//マスク用画像取得用
		int _cg2;
		int _alphaHandle;
};