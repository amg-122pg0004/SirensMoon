#pragma once
#include "Game.h"
#include "picojson/picojson.h"
#include "Math.h"

class Game;
class SplitWindow;

class MapChip{
	public:
		MapChip(Game& game);
		~MapChip();
		int LoadMap(const char *jasonfile);

		/**
		 * \brief マップコリジョンの更新を行います。
		 */
		void Update();


		/**
		 * \brief タイルの表示を行う関数
		 * 
		 * \param windowPos 分割画面の左上の座標
		 * \param cameraPos カメラの座標(基本的に0,0)
		 */
		void Render(Vector2 windowPos,Vector2 cameraPos);

	private:
		Game& _game;

		int _mapSize_W;
		int _mapSize_H;
		int _mapSize_Layer;

		int _chipCount;
		int _chipCount_W;
		int _chipCount_H;
		
		int _chipSize_W;
		int _chipSize_H;

		int* _nMap;

		int* _cgChip;
};
