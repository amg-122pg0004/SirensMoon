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
		int ID;
		std::vector<Vector2> PatrolPoints;
		bool TruckingMode{false};
	};

	/*サーバーデータ構造*/
	struct ServerMachineData {
		Vector2 Position;
		std::string Direction;
	};

	/*サーバータイルセットデータ構造*/
	struct ServerTileData {
		int gid;
		std::string Direction;
	};

	MapChips(Game& game,ModeBase& mode);
	~MapChips();
	bool LoadMap(std::string folderpath, std::string filename);
	void LoadTilesets(picojson::object jsRoot, std::string folderpath);
	void LoadTileLayer(picojson::object);
	void LoadMiniMapLayer(picojson::array aObjects);
	void LoadPlayerLayer(picojson::array aObjects);
	void LoadEnemyLayer(picojson::array aObjects);
	void LoadServerLayer(picojson::array aObjects);
	void LoadItemLayer(picojson::array aObjects);

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

	Vector2 GetPlayerStartPosition(int playerno);
	std::vector<EnemyData> GetEnemyData() { return _enemyDataList; }
	std::vector<EnemyPatrol> GetPatrolPointsVIP() { return _patrolPointsVIP; }
	std::vector<Vector2> GetHPItemData() { return _hpItems; }
	std::vector<Vector2> GetBulletData() { return _bulletItems; }
	std::vector<ServerMachineData> GetServerData() { return _serverMachineDataList; }
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

	std::vector<int> _tilesetsFirstgid;

	/*マップデータ [layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapTileData;
	/*ミニマップデータ [line][plot]*/
	std::vector<std::vector<Vector2>> _minimapData;
	/*プレイヤー初期位置データ[player1か2] */
	std::unordered_map<int,Vector2> _playerStart;
	/*HPアイテムデータ [配置個数分]*/
	std::vector<Vector2> _hpItems;
	/*弾薬アイテムデータ[配置個数分]*/
	std::vector<Vector2> _bulletItems;
	/*通常エネミーデータ[配置個数分]*/
	std::vector<EnemyData> _enemyDataList;
	/*エネミーの巡回ルート*/
	std::unordered_map<int, EnemyPatrol> _patrolPoints;
	/*マップごとの重要エネミー巡回ルート*/
	std::vector<EnemyPatrol> _patrolPointsVIP;
	/*サーバーデータ[配置個数分]*/
	std::vector<ServerMachineData> _serverMachineDataList;
	
	/*マップチップのグラフィックハンドル用コンテナ*/
	/*[タイル用画像の枚数分][画像を分割した際のチップ画像の数]*/
	std::vector<std::vector<int>> _cgChip;
	/*各マップタイルセットのあたり判定を保存するコンテナ*/
	std::vector<std::vector<bool>> _chipCollision;

	/*各クラスが設定されているタイル(gid)を保存*/
	std::vector<int> _gidEnemy;
	std::vector<int> _gidBarrier;
	std::vector<int> _gidItemAmmo;
	std::vector<int> _gidItemHP;
	std::vector<int> _gidPlayer;
	std::vector<ServerTileData> _gidServer;
};