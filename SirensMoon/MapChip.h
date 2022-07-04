#pragma once
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>
#include "Actor.h"

class Game;
class SplitWindow;

class MapChip {
public:
	int _id;
};

class MapChips {
public:
	MapChips(Game& game);
	~MapChips();
	bool LoadMap(std::string folderpath,std::string filename);

	/**
	 * \brief タイルの表示を行う関数
	 *
	 * \param windowPos 分割画面の左上の座標
	 * \param cameraPos カメラの座標(基本的に0,0)
	 */
	void Render(int stageNum,Vector2 windowPos, Vector2 cameraPos);
	
	int GetChipSize_H() { return _chipSize_H; }
	int GetChipSize_W() { return _chipSize_W; }
	
	int CheckHitChipNo(int objectstage, int x, int y);
	int	IsHit(int objectstage, Actor& o, int mxormy);

	//int CheckTransitionChip(int renderstage,Actor& o);
	

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

		/*マップデータ*/
		std::vector<std::vector<std::vector<std::vector<MapChip>>>> _mapData;

		std::vector<int> _cgChip;

};
