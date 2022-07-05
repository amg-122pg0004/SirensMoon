#pragma once
#include <DxLib.h>
#include <vector>
#include "Game.h"
#include "Math.h"

class Darkness {
	public:

		Darkness(Game&);
		/*マスクデータの作成*/
		int MakeDarkness();
		/*マスクデータの削除*/
		void DeleteDarkness();

	private:
		Game& _game;
		int _cg;//マスク用画像取得用
		int _alphaHandle;
};