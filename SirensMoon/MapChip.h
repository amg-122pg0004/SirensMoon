#pragma once
#include <unordered_map>
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>
#include "SquareLight.h"

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

	/*テレポーター(in)データ構造*/
	struct teleporterData {
		Vector2 pos;
		bool random;
		int tereortID;
	};

	/*スイッチデータ構造*/
	struct SwitchData {
		int ID;
		Vector2 pos;
		std::vector<int> links;
	};

	/*Mineデータ構造*/
	struct MineData {
		int ID;
		Vector2 pos;
		int dir;
	};


	MapChips(Game& game,ModeBase& mode);
	~MapChips();


	/**
	 * \brief タイルの表示を行う関数
	 *
	 * \param windowPos 分割画面の左上の座標
	 * \param cameraPos カメラの座標(基本的に0,0)
	 */
	void Render(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	void StandardRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);
	void ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);
	void FrontRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	int GetChipSize_H() { return _chipSize_H; }
	int GetChipSize_W() { return _chipSize_W; }

	Vector2 GetPlayerStartPosition(int playerno);
	std::vector<EnemyData> GetEnemyData() { return _enemyDataList; }
	std::vector<EnemyPatrol> GetPatrolPointsVIP() { return _patrolPointsVIP; }
	std::vector<Vector2> GetHPItemData() { return _hpItems; }
	std::vector<Vector2> GetBulletData() { return _bulletItems; }
	std::vector<ServerMachineData> GetServerData() { return _serverMachineDataList; }
	std::vector<std::pair<int,SquareLight::SquareLightStats>> GetLightData() { return _lightDataList; }
	std::vector<teleporterData> GetteleporterInData() { return _teleporterInDataList; }
	std::unordered_map<int, std::pair<Vector2, bool>> GetteleporterOutData() { return _teleporterOutDataList; }
	std::vector<SwitchData> GetSwitchData() { return _switchDataList; }
	std::vector<std::pair<int, Vector2>>GetDoorData() { return _doorDataList; }
	std::vector<std::pair<int, Vector2>>GetTNTData() { return _tNTDataList; }
	std::vector<MineData> GetMineData() { return _mineDataList; }
	EnemyPatrol FindPatrol(int id);
	std::vector<int> CheckHitChipNo(int objectstage, int x, int y);
	bool IsHit(int objectstage, Actor& o);
	bool IsHitBarrier(int objectstage, Actor& o, int playerno);


private:
	bool LoadMap(std::string folderpath, std::string filename);
	void LoadTilesets(picojson::object jsRoot, std::string folderpath);
	void LoadTileLayer(picojson::object);
	void LoadMiniMapLayer(picojson::array aObjects);
	void LoadPlayerLayer(picojson::array aObjects);
	void LoadEnemyLayer(picojson::array aObjects);
	void LoadServerLayer(picojson::array aObjects);
	void LoadItemLayer(picojson::array aObjects);
	void LoadLightLayer(picojson::array aObjects);
	void LoadGimmickLayer(picojson::array aObjects);

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

	/*奥マップデータ [layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapTileData;
	/*手前マップデータ[layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapFrontTileData;
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
	/*配置ライトデータ<ID,stats>*/
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _lightDataList;
	/*テレポーター入口データ*/
	std::vector<teleporterData> _teleporterInDataList;
	/*テレポーター出口データ<ID,<座標,ランダムフラグ>>*/
	std::unordered_map<int, std::pair<Vector2,bool>> _teleporterOutDataList;
	/*スイッチデータ*/
	std::vector<SwitchData> _switchDataList;
	/*ドアデータ*/
	std::vector<std::pair<int,Vector2>> _doorDataList;
	/*TNTデータ*/
	std::vector<std::pair<int, Vector2>> _tNTDataList;
	/*Mineデータ*/
	std::vector<MineData> _mineDataList;
	
	/*マップチップのグラフィックハンドル用コンテナ*/
	/*[タイル用画像の枚数分][画像を分割した際のチップ画像の数]*/
	std::vector<std::vector<int>> _cgChip;

	/*各マップタイルセットのあたり判定を保存するコンテナ*/
	std::vector<std::vector<bool>> _chipCollision;

	/*手前描画するタイルのgidを保存*/
	std::vector<int> _gidFront;

	/*各クラスが設定されているタイル(gid)を保存*/
	std::vector<int> _gidEnemy;
	std::vector<int> _gidBarrier1;
	std::vector<int> _gidBarrier2;
	std::vector<int> _gidItemAmmo;
	std::vector<int> _gidItemHP;
	std::vector<int> _gidPlayer;
	std::vector<ServerTileData> _gidServer;
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _gidLight;
	std::unordered_map<int, bool> _gidteleportOut;//<boolはランダムにワープするフラグ
	std::unordered_map<int, bool> _gidteleportIn;//<boolはランダム抽選に参加するフラグ
	std::vector<int> _gidSwitch;
	std::vector<int> _gidDoor;
	std::vector<int> _gidTNT;
	std::vector<int> _gidMine;
};