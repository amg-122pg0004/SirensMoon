#pragma once
#include <unordered_map>
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>
#include "Actor.h"

class Game;
class ModeBase;
class SplitWindow;

class MapChip {
public:
	int _id;
};

class MapChips {
public:
	MapChips(Game& game,ModeBase& mode);
	~MapChips();
	bool LoadMap(std::string folderpath, std::string filename);

	/**
	 * \brief タイルの表示を行う関数
	 *
	 * \param windowPos 分割画面の左上の座標
	 * \param cameraPos カメラの座標(基本的に0,0)
	 */
	void Render(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	void StandardRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);
	void ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	int GetChipSize_H() { return _chipSize_H; }
	int GetChipSize_W() { return _chipSize_W; }

	int CheckHitChipNo(int objectstage, int x, int y);
	bool IsHit(int objectstage, Actor& o);


private:
	Game& _game;
	ModeBase& _mode;

	int _mapSize_W;
	int _mapSize_H;
	int _mapSize_Layer;

	int _chipCount;
	int _chipCount_W;
	int _chipCount_H;

	int _chipSize_W;
	int _chipSize_H;

	/*マップデータ ステージNo,レイヤー,*/
	std::vector<std::vector<std::vector<std::vector<MapChip>>>> _mapDataStandard;
	/*ミニマップデータ*/
	std::vector<std::vector<std::vector<Vector2>>> _mapDataRecon;
	/*マップごとのプレイヤーデータ*/
	std::vector<std::vector<Vector2>> _playerStart;
	/*エネミーデータ*/
	struct EnemyData {
		int	   Enemytype;
		Vector2 StartPosition;
		int patrolID;
	};

	/*マップごとのエネミーデータ*/
	std::vector<std::vector<EnemyData>> _enemyDataList;
	/*マップごとのエネミーの巡回ルート*/
	std::vector<std::unordered_map<int, std::vector<Vector2>>> _patrolPoints;
	
	std::vector<int> _cgChip;
};