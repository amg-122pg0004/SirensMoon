#pragma once
#include <DxLib.h>
#include <unordered_map>
#include <vector>
#include <set>
#include <memory>
#include <fstream>
#include "picojson/picojson.h"
#include "Math.h"
#include "ObjectDataStructs.h"
#include "strconv/strconv.h"

class Game;
class ModeBase;
class SplitWindow;
class Actor;

class MapChip {
public:
	MapChip(Game& game,ModeBase& mode,std::string filename);
	~MapChip();
	typedef ObjectDataBase base;
	/**
	 * \brief タイルの表示を行う関数
	 *
	 * \param windowPos 分割画面の左上の座標
	 * \param cameraPos 
	 */
	void Render(Vector2 windowPos, Vector2 cameraPos,std::string layer);

	void MiniMapRender(int stageNum, Vector2 windowPos, Vector2 cameraPos,bool bossflag);

	int GetChipSize_H() { return _chipSize_H; }
	int GetChipSize_W() { return _chipSize_W; }

	PlayerData GetPlayerData(int playerno);

	std::vector<EnemyData> GetEnemyData() { return _enemyDataList; }
	std::vector<EnemyBData> GetEnemyBData() { return _enemyBDataList; }
	std::vector<EnemyPatrol> GetPatrolPointsVIP() { return _patrolPointsVIP; }
	std::vector<Vector2> GetHPItemData() { return _hpItems; }
	std::vector<Vector2> GetBulletData() { return _bulletItems; }
	std::vector<ServerMachineData> GetServerData() { return _serverMachineDataList; }
	std::vector<std::pair<int,SquareLightStats>> GetLightData() { return _lightDataList; }
	std::vector<teleporterData> GetteleporterInData() { return _teleporterInDataList; }
	std::unordered_map<int, std::pair<Vector2, bool>> GetteleporterOutData() { return _teleporterOutDataList; }
	std::vector<SwitchData> GetSwitchData() { return _switchDataList; }
	std::vector<SwitchAreaData> GetSwitchAreaData() { return _switchAreaDataList; }
	std::vector<DoorData>GetDoorData() { return _doorDataList; }
	std::vector<TNTData>GetTNTData() { return _tNTDataList; }
	std::vector<MineData> GetMineData() { return _mineDataList; }
	std::vector<ScreenPumpData> GetScreenPumpData() { return _screenPumpDataList; }
	std::vector<StickyBombData> GetStikyBombData() { return _stickyBombDataList; }
	std::vector<BreakableObjectData> GetBreakableObjectData() { return _breakableObjectData; }
	std::vector<DigitalLetterData> GetDegitalLetterData() { return _deditalLetterData; }
	std::vector<BigServerData> GetBigServerData() { return _bigServerDataList; }
	std::vector<BigGeneratorData> GetBigGeneratorData() { return _bigGeneratorDataList; }
	std::vector<BossGimmickControllerData>GetBossGimmickControllerDataList() { return _bossGimmickControllerDataList; }
	std::vector<BigGunData>GetBigGunDataList() { return _bigGunDataList; }
	EnemyPatrol FindPatrol(int id);
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
	void SetBasicObjectData(picojson::object object, ObjectDataBase data);
	void FindPropertieData(int& data,picojson::array properties,std::string name);
	void FindPropertieData(double& data, picojson::array properties, std::string name);
	void FindPropertieData(bool& data, picojson::array properties, std::string name);
	void FindPropertieData(std::string& data, picojson::array properties, std::string name);
	//template <type>
	//void SetGidData(ObjectDataBase data,std::vector<std::string>& properties);

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
	void LoadBossLayer(picojson::array aObjects);

	void LoadEnemyClass(picojson::object object,EnemyData data);
	void LoadEnemyBClass(picojson::object object, EnemyBData data);

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
	/*ミニマップデータ [line][色,plot]*/
	std::vector<std::pair<unsigned int,std::vector<Vector2>>> _minimapData;
	/*プレイヤー初期位置データ[player1か2] */
	std::unordered_map<int,PlayerData> _playerData;
	/*HPアイテムデータ [配置個数分]*/
	std::vector<Vector2> _hpItems;
	/*弾薬アイテムデータ[配置個数分]*/
	std::vector<Vector2> _bulletItems;
	/*通常エネミーデータ[配置個数分]*/
	std::vector<EnemyData> _enemyDataList;
	/*通常エネミーBデータ[配置個数分]*/
	std::vector<EnemyBData> _enemyBDataList;

	/*エネミーの巡回ルート*/
	std::unordered_map<int, EnemyPatrol> _patrolPoints;
	/*マップごとの重要エネミー巡回ルート*/
	std::vector<EnemyPatrol> _patrolPointsVIP;
	/*サーバーデータ[配置個数分]*/
	std::vector<ServerMachineData> _serverMachineDataList;
	/*配置ライトデータ<ID,stats>*/
	std::vector<std::pair<int,SquareLightStats>> _lightDataList;
	/*テレポーター入口データ*/
	std::vector<teleporterData> _teleporterInDataList;
	/*テレポーター出口データ<ID,<座標,ランダムフラグ>>*/
	std::unordered_map<int, std::pair<Vector2,bool>> _teleporterOutDataList;
	/*スイッチデータ*/
	std::vector<SwitchData> _switchDataList;
	/*スイッチエリアデータ*/
	std::vector<SwitchAreaData> _switchAreaDataList;
	/*ドアデータ*/
	std::vector<DoorData> _doorDataList;
	/*TNTデータ*/
	std::vector<TNTData> _tNTDataList;
	/*Mineデータ*/
	std::vector<MineData> _mineDataList;
	/*ScreenPumpデータ*/
	std::vector<ScreenPumpData> _screenPumpDataList;
	/*StickyBombデータ*/
	std::vector<StickyBombData> _stickyBombDataList;
	/*BrakableObjectデータ*/
	std::vector<BreakableObjectData> _breakableObjectData;
	/*DegitalLetterデータ*/
	std::vector<DigitalLetterData> _deditalLetterData;
	/*BigServerDataデータ*/
	std::vector<BigServerData> _bigServerDataList;
	/*BigGeneratorDataデータ*/
	std::vector<BigGeneratorData> _bigGeneratorDataList;
	/*BossGimmickControllerDataデータ*/
	std::vector<BossGimmickControllerData> _bossGimmickControllerDataList;
	/*BossGimmickControllerDataデータ*/
	std::vector<BigGunData> _bigGunDataList;

	
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
	/*
	std::vector<int> _gidEnemy;
	std::vector<EnemyBData> _gidEnemyB;
	std::vector<int> _gidBarrier1;
	std::vector<int> _gidBarrier2;
	std::vector<int> _gidItemAmmo;
	std::vector<int> _gidItemHP;
	std::vector<std::pair<int,PlayerData>> _gidPlayer;
	std::vector<ServerTileData> _gidServer;
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _gidLight;
	std::unordered_map<int, bool> _gidteleportOut;//<boolはランダムにワープするフラグ
	std::unordered_map<int, bool> _gidteleportIn;//<boolはランダム抽選に参加するフラグ
	std::vector<std::pair<int,bool>> _gidSwitch;
	std::vector<int> _gidSwitchArea;
	std::vector<DoorData> _gidDoor;
	std::vector<TNTData> _gidTNT;
	std::vector<int> _gidMine;
	std::vector<int> _gidScreenPump;
	std::vector<int> _gidStickyBomb;
	std::vector<int> _gidBreakableObject;
	std::vector<int> _gidDegitalLetter;
	std::vector<int> _gidBigServer;
	std::vector<int> _gidBigGenerator;
	std::vector<int> _gidBigGun;
	std::vector<int> _gidBossGimmickController;
	*/

	std::unordered_map<int,ObjectDataBase> _objectGIDs;
};