#pragma once
#include <DxLib.h>
#include <unordered_map>
#include <vector>
#include <set>
#include <memory>
#include <fstream>
#include "picojson/picojson.h"
#include "Collision.h"
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
	std::vector<HPItemData> GetHPItemData() { return _hpItems; }
	std::vector<BulletItemData> GetBulletData() { return _bulletItems; }
	std::vector<ServerMachineData> GetServerData() { return _serverMachineDataList; }
	std::vector<SquareLightStats> GetLightData() { return _lightDataList; }
	std::vector<teleporterData> GetteleporterInData() { return _teleporterInDataList; }
	std::vector<TeleporterOutData> GetteleporterOutData() { return _teleporterOutDataList; }
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

	bool LoadMap(std::string folderpath, std::string filename);
	void LoadTilesets(picojson::object jsRoot, std::string folderpath);
	void LoadTileLayer(picojson::object);
	void LoadMiniMapLayer(picojson::array aObjects);
	void LoadEnemyLayer(picojson::array aObjects);
	void LoadServerLayer(picojson::array aObjects);

	/*配置オブジェクト読み込み用関数*/
	void LoadBarrierClass(picojson::object object, BarrierData data);
	void LoadBossGeneratorClass(picojson::object object, BigGeneratorData data);
	void LoadBossRailGunClass(picojson::object object, BigGunData data);
	void LoadBossServerClass(picojson::object object, BigServerData data);
	void LoadBossTriggerClass(picojson::object object, BossGimmickControllerData data);
	void LoadBreakableObjectClass(picojson::object object,BreakableObjectData data);
	void LoadDigitalLetterClass(picojson::object object, DigitalLetterData data);
	void LoadEnemyClass(picojson::object object,EnemyData data);
	void LoadEnemyBClass(picojson::object object, EnemyBData data);
	void LoadDoorClass(picojson::object object,DoorData data);
	void LoadItemAmmoClass(picojson::object object, BulletItemData data);
	void LoadItemHPClass(picojson::object object, HPItemData data);
	void LoadLightClass(picojson::object object, SquareLightStats data);
	void LoadMineClass(picojson::object object, MineData data);
	void LoadPlayerClass(picojson::object object, PlayerData data);
	void LoadScreenPumpClass(picojson::object object, ScreenPumpData data);
	void LoadServerClass(picojson::object object, ServerMachineData& data);
	void LoadStickyBombClass(picojson::object object, StickyBombData data);
	void LoadSwitchClass(picojson::object object, SwitchData data);
	void LoadSwitchAreaClass(picojson::object object, SwitchAreaData data);
	void LoadTeleport_INClass(picojson::object object, teleporterData data);
	void LoadTeleport_OUTClass(picojson::object object, TeleporterOutData data);
	void LoadTNTClass(picojson::object object, TNTData data);

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
	/*各タイルセットの最初のgid*/
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
	/*HPアイテムデータ*/
	std::vector<HPItemData> _hpItems;
	/*弾薬アイテムデータ*/
	std::vector<BulletItemData> _bulletItems;
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
	/*配置ライトデータ*/
	std::vector<SquareLightStats> _lightDataList;
	/*テレポーター入口データ*/
	std::vector<teleporterData> _teleporterInDataList;
	/*テレポーター出口データ*/
	std::vector<TeleporterOutData> _teleporterOutDataList;
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
	/*手前描画するタイルのgidを保存*/
	std::vector<int> _gidFront;
	/*奥描画するタイルのgidを保存*/
	std::vector<int> _gidBack;
	/*あたり判定が設定されているタイルのGIDを保存するコンテナ*/
	std::vector<int> _chipCollision;
	std::vector<int> _gidBarrier1, _gidBarrier2;

	/*オブジェクトのGIDを保存するコンテナ*/
	std::unordered_map<int,ObjectDataBase> _objectGIDs;
};