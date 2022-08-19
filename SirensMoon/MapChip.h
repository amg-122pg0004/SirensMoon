#pragma once
#include <unordered_map>
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>
#include <set>
#include "SquareLight.h"
#include "ObjectDataStructs.h"

class Game;
class ModeBase;
class SplitWindow;
class Actor;

class MapChips {
public:
	MapChips(Game& game,ModeBase& mode);
	~MapChips();

	typedef ObjectDataStructs St;

	/**
	 * \brief タイルの表示を行う関数
	 *
	 * \param windowPos 分割画面の左上の座標
	 * \param cameraPos 
	 */
	void Render(Vector2 windowPos, Vector2 cameraPos,std::string layer);

	void ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	int GetChipSize_H() { return _chipSize_H; }
	int GetChipSize_W() { return _chipSize_W; }

	St::PlayerData GetPlayerData(int playerno);

	std::vector<St::EnemyData> GetEnemyData() { return _enemyDataList; }
	std::vector<St::EnemyBData> GetEnemyBData() { return _enemyBDataList; }
	std::vector<St::EnemyPatrol> GetPatrolPointsVIP() { return _patrolPointsVIP; }
	std::vector<Vector2> GetHPItemData() { return _hpItems; }
	std::vector<Vector2> GetBulletData() { return _bulletItems; }
	std::vector<St::ServerMachineData> GetServerData() { return _serverMachineDataList; }
	std::vector<std::pair<int,SquareLight::SquareLightStats>> GetLightData() { return _lightDataList; }
	std::vector<St::teleporterData> GetteleporterInData() { return _teleporterInDataList; }
	std::unordered_map<int, std::pair<Vector2, bool>> GetteleporterOutData() { return _teleporterOutDataList; }
	std::vector<St::SwitchData> GetSwitchData() { return _switchDataList; }
	std::vector<std::pair<int, Vector2>>GetDoorData() { return _doorDataList; }
	std::vector<std::pair<int, Vector2>>GetTNTData() { return _tNTDataList; }
	std::vector<St::MineData> GetMineData() { return _mineDataList; }
	std::vector<St::StickyBombData> GetStikyBombData() { return _stickyBombDataList; }
	std::vector<St::BreakableObjectData> GetBreakableObjectData() { return _breakableObjectData; }
	St::EnemyPatrol FindPatrol(int id);
	std::vector<int> CheckHitChipNo(int x, int y, bool backlayer);
	/**
	 * \brief マップチップとアクターの接触判定
	 * 
	 * \param col アクターのコリジョンボックス
	 * \param backlayer　trueなら後ろレンダリングマップチップとの判定をとる
	 * \return 当たったらtrue
	 */
	bool IsHit(AABB col,bool backlayer);
	bool IsHitBarrier(AABB col, int playerno);
	bool IsHit(std::set<std::pair<int, int>>);


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

	void LoadEnemyClass(picojson::object object,St::EnemyData data);
	void LoadEnemyBClass(picojson::object object, St::EnemyBData data);

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
	std::vector<std::vector<std::vector<int>>> _mapBackTileData;
	/*中間マップデータ [layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapTileData;
	/*手前マップデータ[layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapFrontTileData;
	/*ミニマップデータ [line][plot]*/
	std::vector<std::vector<Vector2>> _minimapData;
	/*プレイヤー初期位置データ[player1か2] */
	std::unordered_map<int,St::PlayerData> _playerData;
	/*HPアイテムデータ [配置個数分]*/
	std::vector<Vector2> _hpItems;
	/*弾薬アイテムデータ[配置個数分]*/
	std::vector<Vector2> _bulletItems;
	/*通常エネミーデータ[配置個数分]*/
	std::vector<St::EnemyData> _enemyDataList;
	/*通常エネミーBデータ[配置個数分]*/
	std::vector<St::EnemyBData> _enemyBDataList;

	/*エネミーの巡回ルート*/
	std::unordered_map<int, St::EnemyPatrol> _patrolPoints;
	/*マップごとの重要エネミー巡回ルート*/
	std::vector<St::EnemyPatrol> _patrolPointsVIP;
	/*サーバーデータ[配置個数分]*/
	std::vector<St::ServerMachineData> _serverMachineDataList;
	/*配置ライトデータ<ID,stats>*/
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _lightDataList;
	/*テレポーター入口データ*/
	std::vector<St::teleporterData> _teleporterInDataList;
	/*テレポーター出口データ<ID,<座標,ランダムフラグ>>*/
	std::unordered_map<int, std::pair<Vector2,bool>> _teleporterOutDataList;
	/*スイッチデータ*/
	std::vector<St::SwitchData> _switchDataList;
	/*ドアデータ*/
	std::vector<std::pair<int,Vector2>> _doorDataList;
	/*TNTデータ*/
	std::vector<std::pair<int, Vector2>> _tNTDataList;
	/*Mineデータ*/
	std::vector<St::MineData> _mineDataList;
	/*StickyBombデータ*/
	std::vector<St::StickyBombData> _stickyBombDataList;
	/*BrakableObjectデータ*/
	std::vector<St::BreakableObjectData> _breakableObjectData;
	
	/*マップチップのグラフィックハンドル用コンテナ*/
	/*[タイル用画像の枚数分][画像を分割した際のチップ画像の数]*/
	std::vector<std::vector<int>> _cgChip;

	/*あたり判定が設定されているタイルのGIDを保存するコンテナ*/
	std::vector<int> _chipCollision;

	/*手前描画するタイルのgidを保存*/
	std::vector<int> _gidFront;
	/*奥描画するタイルのgidを保存*/
	std::vector<int> _gidBack;

	/*各クラスが設定されているタイル(gid)を保存*/
	std::vector<int> _gidEnemy;
	std::vector<St::EnemyBData> _gidEnemyB;
	std::vector<int> _gidBarrier1;
	std::vector<int> _gidBarrier2;
	std::vector<int> _gidItemAmmo;
	std::vector<int> _gidItemHP;
	std::vector<std::pair<int,St::PlayerData>> _gidPlayer;
	std::vector<St::ServerTileData> _gidServer;
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _gidLight;
	std::unordered_map<int, bool> _gidteleportOut;//<boolはランダムにワープするフラグ
	std::unordered_map<int, bool> _gidteleportIn;//<boolはランダム抽選に参加するフラグ
	std::vector<int> _gidSwitch;
	std::vector<int> _gidDoor;
	std::vector<int> _gidTNT;
	std::vector<int> _gidMine;
	std::vector<int> _gidStickyBomb;
	std::vector<int> _gidBreakableObject;
};