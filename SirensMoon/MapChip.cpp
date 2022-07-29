#include <DxLib.h>
#include"MapChip.h"
#include "picojson/picojson.h"
#include "Camera.h"
#include "ImageServer.h"
#include <memory>
#include <fstream>
#include <unordered_map>

MapChips::MapChips(Game& game, ModeBase& mode) :_game{ game }, _mode{mode}{
	_mapDataStandard.clear();
	_mapDataRecon.clear();
	LoadMap("resource/", "TestMap_02.json");
}

MapChips::~MapChips() {
	_mapDataStandard.clear();
	_mapDataRecon.clear();
}

bool MapChips::LoadMap(std::string folderpath, std::string filename) 
{

	// ファイルからjsonデータの読み込み
	std::ifstream ifs(folderpath + filename);
	picojson::value json;
	ifs >> json;

	// jsonデータからパラメータを取得
	picojson::object jsRoot = json.get<picojson::object>();
	_mapSize_W = (int)jsRoot["width"].get<double>();
	_mapSize_H = (int)jsRoot["height"].get<double>();

	// タイルセット取得(1つのみ対応)
	picojson::array aTileSets = jsRoot["tilesets"].get<picojson::array>();
	for (int i = 0; i < aTileSets.size(); ++i) {
		picojson::object jsTile = aTileSets[i].get<picojson::object>();
		_tilesetsFirstgid.push_back((int)jsTile["firstgid"].get<double>());
		_chipCount = (int)jsTile["tilecount"].get<double>();

		_chipCount_W = (int)jsTile["columns"].get<double>();
		//_chipCount_H = (_chipCount / _chipCount_W);		// 計算で出す

		_chipSize_W = (int)jsRoot["tilewidth"].get<double>();
		_chipSize_H = (int)jsRoot["tileheight"].get<double>();
		auto a= (int)jsTile["imageheight"].get<double>();
		_chipCount_H = a / _chipSize_H;
		std::string strChipFile = jsTile["image"].get<std::string>();       // 画像ファイル名
	// チップ画像読み込み
		std::vector<int> cghandle;
		cghandle.resize(_chipCount);
		ImageServer::LoadDivGraph((folderpath + strChipFile).c_str()
			, _chipCount, _chipCount_W, _chipCount_H
			, _chipSize_W, _chipSize_H
			, cghandle.data());
		_cgChip.push_back(cghandle);
		//チップデータ読み込み
		std::vector<bool> chip_col;
		chip_col.push_back(0);
		picojson::array  tiles = jsTile["tiles"].get<picojson::array>();
		for (auto i = tiles.begin(); i != tiles.end();++i) {
			/*各クラスgid読み込み*/
			if ((*i).get<picojson::object>()["class"].is<std::string>()) {
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Enemy") {
					_gidEnemy.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>()+1));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Barrier") {
					_gidBarrier.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>()+1));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "ItemAmmo") {
					_gidItemAmmo.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>()+1));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "ItemHP") {
					_gidItemHP.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>()+1));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Player") {
					_gidPlayer.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>()+1));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Server") {
					_gidServer.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>()+1));
				}
			}
			// チップコリジョンデータ読み込み
			if ((*i).get<picojson::object>()["properties"].is<picojson::array>()) {
				auto properties = (*i).get<picojson::object>()["properties"].get<picojson::array>();
				for (int i2 = 0; i2 < properties.size();++i2) {
					if (properties[i2].get<picojson::object>()["name"].is<std::string>()) {
						if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Collision") {
							auto debug = properties[i2].get<picojson::object>()["value"].get<bool>();
							chip_col.push_back(properties[i2].get<picojson::object>()["value"].get<bool>());
							break;
						}
					}
					chip_col.push_back(0);
				}
			}
			else {
				chip_col.push_back(0);
			}
		}
		_chipCollision.push_back(chip_col);
	}


	// レイヤー情報の取得
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();

	// レイヤー内データの取得
	std::vector<std::vector<std::vector<int>>>onestagedata;
	/*一つのステージのポリゴンデータ*/
	std::vector<std::vector<Vector2>>  onestagepolygons;
	/*1ステージ分のエネミーデータ*/
	std::vector<EnemyData> aEnemyData;
	/*1ステージ分のサーバーデータ*/
	std::vector<ServerMachineData> aServerData;
	for (int i = 0; i < aLayers.size(); i++) 
	{

		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// レイヤーオブジェクト

		// レイヤー種類が「tilelayer」のもの
		if (jsLayer["type"].get<std::string>() == "tilelayer") 
		{
			picojson::array aData = jsLayer["data"].get<picojson::array>();			// マップ配列
			int index = 0;
			std::vector<std::vector<int>>	vMapLayer;	// 1レイヤー分のデータ
			for (int y = 0; y < _mapSize_H; y++) {
				std::vector<int>	vMapLine;	// 1行分のデータ
				for (int x = 0; x < _mapSize_W; x++) {
					int chip_id;
					chip_id = (int)aData[index].get<double>();
					vMapLine.push_back(chip_id);
					index++;
				}
				vMapLayer.push_back(vMapLine);
			}
			// レイヤーデータを追加
			onestagedata.push_back(vMapLayer);
		}
		/*レイヤーの名前がMiniMapの物を取得*/
		else if (jsLayer["name"].get<std::string>() == "MiniMap")
		{
			/*オブジェクト（ポリゴン）の数を確認、回数分ループ*/
			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			for (int i = 0; i < aObjects.size(); ++i)
			{
			std::string linestyle = "NULL";
			/*polylineが存在するか確認*/
			if (aObjects[i].get<picojson::object>()["polyline"].is<picojson::array>()) {
				linestyle = "polyline";
			}
			/*polygonが存在するか確認*/
			else if (aObjects[i].get<picojson::object>()["polygon"].is<picojson::array>()) {
				linestyle = "polygon";
			}
				/*一つのポリゴンの頂点データ*/
				std::vector<Vector2> polygonplots;
				/*ポリゴンの頂点数分ループ*/
				picojson::array polylineplots = aObjects[i].get<picojson::object>()[linestyle].get<picojson::array>();
				for (int i2 = 0; i2 < polylineplots.size(); ++i2)
				{
					auto x = polylineplots[i2].get<picojson::object>()["x"].get<double>()
						+ aObjects[i].get<picojson::object>()["x"].get<double>();
					auto y = polylineplots[i2].get<picojson::object>()["y"].get<double>()
						+ aObjects[i].get<picojson::object>()["y"].get<double>();
					Vector2 plot = { x,y };
					polygonplots.push_back(plot);
				}
				onestagepolygons.push_back(polygonplots);
			}
			_mapDataRecon.push_back(onestagepolygons);
		}
		else if (jsLayer["name"].get<std::string>() == "Player") 
		{

			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			std::vector<Vector2> aStartPoint;
			for (int i = 0; i < aObjects.size(); ++i) {
				double posX = aObjects[i].get<picojson::object>()["x"].get<double>();
				double posY = aObjects[i].get<picojson::object>()["y"].get<double>();

				Vector2 pos = { posX,posY };

				aStartPoint.push_back(pos);
			}
			_playerStart.push_back(aStartPoint);
		}
		else if (jsLayer["name"].get<std::string>() == "Item") {
			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			std::vector<Vector2> aHPPosition;
			std::vector<Vector2> aBulletPosition;
			for (int i = 0; i < aObjects.size(); ++i) {
				double posX, posY;
				for (auto gid : _gidItemAmmo) {
					if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid) {
						posX = aObjects[i].get<picojson::object>()["x"].get<double>();
						posY = aObjects[i].get<picojson::object>()["y"].get<double>();
						Vector2 pos = { posX,posY };
						aBulletPosition.push_back(pos);
					}
				}
				for (auto gid : _gidItemHP) {
					if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid) {
						posX = aObjects[i].get<picojson::object>()["x"].get<double>();
						posY = aObjects[i].get<picojson::object>()["y"].get<double>();
						Vector2 pos = { posX,posY };
						aHPPosition.push_back(pos);
					}
				}
			}
			_hpItems.push_back(aHPPosition);
			_bulletItems.push_back(aBulletPosition);
		}
		else if (jsLayer["name"].get<std::string>() == "Enemy") 
		{
			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			for (int i = 0; i < aObjects.size(); ++i) {
				/*マップタイル3番はエネミー*/
				if (aObjects[i].get<picojson::object>()["gid"].is<double>()){
					for (auto gid : _gidEnemy) {
						if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid) {

							int aEnemyID;
							int     aEnemyType;
							Vector2	aEnemyPosition;
							int aPatrolID;

							aEnemyID = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());

							picojson::array properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();

							aEnemyType = static_cast<int>(properties[0].get<picojson::object>()["value"].get<double>());
							aPatrolID = static_cast<int>(properties[1].get<picojson::object>()["value"].get<double>());

							double posX = aObjects[i].get<picojson::object>()["x"].get<double>();
							double posY = aObjects[i].get<picojson::object>()["y"].get<double>();
							aEnemyPosition = { posX,posY };
							if (aEnemyType == 0) {
								aEnemyData.push_back({ aEnemyID,aEnemyType, aEnemyPosition, aPatrolID });
							}
						}
					}
				}
				/*height=0はPolylineかpolygonによる巡回ルートオブジェクト*/
				else if(aObjects[i].get<picojson::object>()["polygon"].is<picojson::array>()||
					aObjects[i].get<picojson::object>()["polyline"].is<picojson::array>()) {
					/*敵1体分の巡回ルート*/
					EnemyPatrol aPatrolData;
					std::string linestyle = "null";
					/*polylineが存在するか確認*/
					if (aObjects[i].get<picojson::object>()["polyline"].is<picojson::array>()) {
						linestyle = "polyline";
						aPatrolData.TruckingMode = 0;
					}
					/*polygonが存在するか確認*/
					else if (aObjects[i].get<picojson::object>()["polygon"].is<picojson::array>()) {
						linestyle = "polygon";
						aPatrolData.TruckingMode = 1;
					}
					/*polylineかpolygonがあれば巡回座標読み込み*/
					if (linestyle != "null") 
					{
						picojson::array pointsArray = aObjects[i].get<picojson::object>()[linestyle].get<picojson::array>();
						for (int p = 0; p < pointsArray.size(); ++p) 
						{
							double x = pointsArray[p].get <picojson::object>()["x"].get<double>();
							double y = pointsArray[p].get <picojson::object>()["y"].get<double>();
							x += aObjects[i].get<picojson::object>()["x"].get<double>();
							y += aObjects[i].get<picojson::object>()["y"].get<double>();
							Vector2 pos = { x,y };
							aPatrolData.PatrolPoints.push_back(pos);
						}
						/*巡回ルートに対応するID読み混み*/
						int id = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
						aPatrolData.ID = id;
						/*mapにIDをキーとして巡回ルート登録*/
						_patrolPoints[id] = aPatrolData;
					}
				}
			}
			_enemyDataList.push_back(aEnemyData);
		}
		else if (jsLayer["name"].get<std::string>() == "Server") {
			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			for (int i = 0; i < aObjects.size(); ++i) {
			/*マップタイル3番はエネミー*/
				if (aObjects[i].get<picojson::object>()["gid"].is<double>()) {
				/*残りはサーバーのデータ*/
				Vector2 pos{ 0,0 };
				int dir{ -1 };
				if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>()) {
					picojson::array properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
					for (int i2 = 0; i2<properties.size(); ++i2) {
						if (properties[i2].get<picojson::object>()["value"].is<std::string>()) {
							if (properties[i2].get<picojson::object>()["value"].get<std::string>() == "up") {
								dir = 1;
							}
							if (properties[i2].get<picojson::object>()["value"].get<std::string>() == "down") {
								dir = 3;
							}
							if (properties[i2].get<picojson::object>()["value"].get<std::string>() == "right") {
								dir = 2;
							}
							if (properties[i2].get<picojson::object>()["value"].get<std::string>() == "left") {
								dir = 4;
							}
						}
					}
					if (dir != -1) {
						pos.x = aObjects[i].get<picojson::object>()["x"].get<double>();
						pos.y = aObjects[i].get<picojson::object>()["y"].get<double>();
						aServerData.push_back({ pos,dir });
					}
				}
			}
			/*height=0はPolylineかpolygonによる巡回ルートオブジェクト*/
			if (aObjects[i].get<picojson::object>()["polygon"].is<picojson::array>() ||
				aObjects[i].get<picojson::object>()["polyline"].is<picojson::array>()) {
				/*敵1体分の巡回ルート*/
				EnemyPatrol aPatrolData;
				std::string linestyle = "null";
				/*polylineが存在するか確認*/
				if (aObjects[i].get<picojson::object>()["polyline"].is<picojson::array>()) {
					linestyle = "polyline";
					aPatrolData.TruckingMode = 0;
				}
				/*polygonが存在するか確認*/
				else if (aObjects[i].get<picojson::object>()["polygon"].is<picojson::array>()) {
					linestyle = "polygon";
					aPatrolData.TruckingMode = 1;
				}
				/*polylineかpolygonがあれば巡回座標読み込み*/
				if (linestyle != "null")
				{
					picojson::array pointsArray = aObjects[i].get<picojson::object>()[linestyle].get<picojson::array>();
					for (int p = 0; p < pointsArray.size(); ++p)
					{
						double x = pointsArray[p].get <picojson::object>()["x"].get<double>();
						double y = pointsArray[p].get <picojson::object>()["y"].get<double>();
						x += aObjects[i].get<picojson::object>()["x"].get<double>();
						y += aObjects[i].get<picojson::object>()["y"].get<double>();
						Vector2 pos = { x,y };
						aPatrolData.PatrolPoints.push_back(pos);
					}
					/*巡回ルートに対応するID読み混み*/
					int id = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
					aPatrolData.ID = id;
					/*mapにIDをキーとして巡回ルート登録*/
					_patrolPointsVIP.push_back(aPatrolData);
				}
			}
		}
		_serverMachineDataList.push_back(aServerData);
		}
	}
	_mapDataStandard.push_back(onestagedata);
	return true;
}

void MapChips::Render(int stageNum, Vector2 windowPos, Vector2 cameraPos) {
	if (windowPos.x < 100) {
		StandardRender(stageNum, windowPos, cameraPos);
	}
	else {
		ReconRender(stageNum, windowPos, cameraPos);
	}
}

void MapChips::StandardRender(int stageNum,Vector2 windowPos,Vector2 cameraPos) {

	int x, y;
	for (int layer = 0; layer < _mapDataStandard[stageNum].size(); ++layer)
	{
		for (y = 0; y < _mapSize_H; ++y)
		{
			for(x = 0 ; x < _mapSize_W ; ++x)
			{
				int layerstart = _mapSize_W * _mapSize_H * layer;
				int index = y * _mapSize_W + x;
				int pos_x = x * _chipSize_W +static_cast<int>(windowPos.x) - static_cast<int>(cameraPos.x);
				int pos_y = y * _chipSize_H + static_cast<int>(windowPos.y) - static_cast<int>(cameraPos.y);
				int chip_no = _mapDataStandard[stageNum][layer][y][x];
				chip_no--;
				int chiplayer = 0;
				for (int i = _cgChip.size()-1; 0<=i; --i) {
					if (chip_no >= (_tilesetsFirstgid[i] - 1)) {
						chiplayer = i;
						chip_no = chip_no - (_tilesetsFirstgid[i] - 1);
						break;
					}
				}
				if (chip_no >= 0) {
					DrawGraph(pos_x, pos_y, _cgChip[chiplayer][chip_no], TRUE);
				}
			}
		}
	}
}

void MapChips::ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos) 
{
	for (int i = 0; i < _mapDataRecon[stageNum].size(); ++i) 
	{
		int plotsize = static_cast<int>(_mapDataRecon[stageNum][i].size());
		for (int plot = 0; plot < plotsize; ++plot) 
		{
			//float scale =static_cast<float>( 410.0/3240.0*0.97);
			float scale = static_cast<float>(410.0 / 4320.0 * 0.97);
			DrawLineAA(static_cast<float>(_mapDataRecon[stageNum][i][plot].x*scale + windowPos.x),
				static_cast<float>(_mapDataRecon[stageNum][i][plot].y*scale + windowPos.y ),
				static_cast<float>(_mapDataRecon[stageNum][i][(plot + 1) % plotsize].x *scale+ windowPos.x),
				static_cast<float>(_mapDataRecon[stageNum][i][(plot + 1) % plotsize].y *scale+ windowPos.y ),
				GetColor(0, 255, 255));
		}
	}
}

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
std::vector<int> MapChips::CheckHitChipNo(int stagenum,int x, int y)
{
	std::vector<int> v_chip_no;
	// マップチップ位置はマップデータからはみ出ているか？
	if (0 <= x && x < _mapSize_W && 0 <= y && y < _mapSize_H)
	{	
		// マップチップIDが0以外は当たり判定を行う
		for( int layer = 0; layer < _mapDataStandard[stagenum].size(); ++layer) {
			int chip_no = _mapDataStandard[stagenum][layer][y][x];
			// 当たった
			v_chip_no.emplace_back(chip_no);
		}
	}
	// 何もマップチップと当たっていなければ-1を入れる
	if (v_chip_no.size() == 0) {
		v_chip_no.emplace_back(-1);
	}
	return v_chip_no;
}


// オブジェクトとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//  
//   o = オブジェクト
// 戻値：
//   0 : 当たってない
//   1 : 当たった
bool MapChips::IsHit(int objectstage,Actor& o)
{
	int x, y;
	int dxordy=0;
	// キャラ矩形を作成する
	int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
	l = static_cast<int>(o.GetPosition().x);
	t = static_cast<int>(o.GetPosition().y);
	r = static_cast<int>(o.GetPosition().x+o.GetSize().x);
	b = static_cast<int>(o.GetPosition().y+o.GetSize().y);
	// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
	for (y = t / _chipSize_H; y <= b / _chipSize_H; y++)
	{
		for (x = l / _chipSize_W; x <= r / _chipSize_W; x++)
		{
			// (x,y)は、マップチップの座標（チップ単位）
			// この位置のチップは当たるか？
			std::vector<int> v_chip_no = CheckHitChipNo(objectstage,x,y);
			for (int chip_no : v_chip_no) {
				if (_chipCollision[objectstage][chip_no]){
					return 1;
				}
			}
		}
	}
	// 当たらなかった
	return 0;
}

// オブジェクトとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//  
//   o = オブジェクト
// 戻値：
//   0 : 当たってない
//   1 : 当たった
bool MapChips::IsHitBarrier(int objectstage, Actor& o,int playerno)
{
	int x, y;
	int dxordy = 0;

	// キャラ矩形を作成する
	int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
	l = static_cast<int>(o.GetPosition().x);
	t = static_cast<int>(o.GetPosition().y);
	r = static_cast<int>(o.GetPosition().x + o.GetSize().x);
	b = static_cast<int>(o.GetPosition().y + o.GetSize().y);

	// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
	for (y = t / _chipSize_H; y <= b / _chipSize_H; y++)
	{
		for (x = l / _chipSize_W; x <= r / _chipSize_W; x++)
		{
			// (x,y)は、マップチップの座標（チップ単位）
			// この位置のチップは当たるか？
			std::vector<int> v_chip_no = CheckHitChipNo(objectstage, x, y);
			for (int chip_no : v_chip_no) {
				if (playerno == 0) {
					if (chip_no == 10)
					{	// このチップと当たった。
						// 当たったので戻る
						return 1;
					}
				}
				if (playerno == 1) {
					if (chip_no == 11)
					{	// このチップと当たった。
						// 当たったので戻る
						return 1;
					}
				}
			}
		}
	}
	// 当たらなかった
	return 0;
}

MapChips::EnemyPatrol MapChips::FindPatrol(int id){
	auto points = _patrolPoints.find(id);
	if (points != _patrolPoints.end()) {
		return points->second;
	}

	return {-1, { {0,0} }, false };
}