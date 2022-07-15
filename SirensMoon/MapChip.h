#pragma once
#include <unordered_map>
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>

class Game;
class ModeBase;
class SplitWindow;
class Actor;

class MapChip {
public:
	int _id;
};

class MapChips {
public:
	/*エネミーデータ*/
	struct EnemyData {
		int	   Enemytype;
		Vector2 StartPosition;
		int patrolID;
	};

	/*エネミー巡回経路データ*/
	struct EnemyPatrol {
		std::vector<Vector2> PatrolPoints;
		bool TruckingMode;
	};

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

	Vector2 GetPlayerStartPosition(int playerno) { return _playerStart[0][playerno]; }
	std::vector<EnemyData> GetEnemyData() { return _enemyDataList[0]; }
	EnemyPatrol FindPatrol(int id);
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


	/*マップごとのエネミーデータ*/
	std::vector<std::vector<EnemyData>> _enemyDataList;
	/*マップごとのエネミーの巡回ルート*/
	std::unordered_map<int, EnemyPatrol> _patrolPoints;
	
	std::vector<int> _cgChip;
};