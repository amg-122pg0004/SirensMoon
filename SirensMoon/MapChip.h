#pragma once
#include <unordered_map>
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>

class Game;
class ModeBase;
class SplitWindow;
class Actor;

class MapChips {
public:
	/*エネミーデータ構造*/
	struct EnemyData {
		int ID;
		int	Enemytype;
		Vector2 StartPosition;
		int patrolID;
	};

	/*エネミー巡回経路データ構造*/
	struct EnemyPatrol {
		std::vector<Vector2> PatrolPoints;
		bool TruckingMode{false};
	};

	/*サーバーデータ構造*/
	struct ServerMachineData {
		Vector2 Position;
		int Direction;
		int SpawnEnemyID;
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
	std::vector<Vector2> GetHPItemData() { return _hpItems[0]; }
	std::vector<Vector2> GetBulletData() { return _bulletItems[0]; }
	EnemyPatrol FindPatrol(int id);
	std::vector<int> CheckHitChipNo(int objectstage, int x, int y);
	bool IsHit(int objectstage, Actor& o);
	bool IsHitBarrier(int objectstage, Actor& o, int playerno);


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
	std::vector<std::vector<std::vector<std::vector<int>>>> _mapDataStandard;
	/*ミニマップデータ*/
	std::vector<std::vector<std::vector<Vector2>>> _mapDataRecon;
	/*マップごとのプレイヤーデータ*/
	std::vector<std::vector<Vector2>> _playerStart;
	/*マップごとのHPアイテムデータ*/
	std::vector<std::vector<Vector2>> _hpItems;
	/*マップごとの弾薬アイテムデータ*/
	std::vector<std::vector<Vector2>> _bulletItems;

	/*マップごとのエネミーデータ*/
	std::vector<std::vector<EnemyData>> _enemyDataList;
	/*マップごとのエネミーの巡回ルート*/
	std::unordered_map<int, EnemyPatrol> _patrolPoints;
	/*マップごとのサーバーデータ*/
	std::vector<std::vector<ServerMachineData>> _serverMachineData;
	
	std::vector<int> _cgChip;
};