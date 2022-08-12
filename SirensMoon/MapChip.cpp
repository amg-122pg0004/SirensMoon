#include <DxLib.h>
#include"MapChip.h"
#include "picojson/picojson.h"
#include "Camera.h"
#include "ImageServer.h"
#include <memory>
#include <fstream>
#include <unordered_map>

MapChips::MapChips(Game& game, ModeBase& mode) :_game{ game }, _mode{mode}{
	_mapTileData.clear();
	_minimapData.clear();
	LoadMap("resource/", "TestMap_02.json");
}

MapChips::~MapChips() {
	_mapTileData.clear();
	_minimapData.clear();
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


	LoadTilesets(jsRoot,folderpath);

	// レイヤー情報の取得
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();

	for (int i = 0; i < aLayers.size(); i++)
	{
		
		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// レイヤーオブジェクト

		/*オブジェクトレイヤーに存在するオブジェクト配列*/
		picojson::array aObjects;
		if (jsLayer["objects"].is<picojson::array>()) {
			aObjects = jsLayer["objects"].get<picojson::array>();
		}
		// レイヤー種類が「tilelayer」のもの
		if (jsLayer["type"].get<std::string>() == "tilelayer")
		{
			LoadTileLayer(jsLayer);
		}
		/*レイヤーの名前がMiniMapの物を取得*/
		else if (jsLayer["name"].get<std::string>() == "MiniMap")
		{
			LoadMiniMapLayer(aObjects);
		}
		else if (jsLayer["name"].get<std::string>() == "Player")
		{
			LoadPlayerLayer(aObjects);
		}
		else if (jsLayer["name"].get<std::string>() == "Item") {
			LoadItemLayer(aObjects);
		}
		else if (jsLayer["name"].get<std::string>() == "Enemy")
		{
			LoadEnemyLayer(aObjects);
		}
		else if (jsLayer["name"].get<std::string>() == "Server") {
			LoadServerLayer(aObjects);
		}
		else if (jsLayer["name"].get<std::string>() == "Light") {
			LoadLightLayer(aObjects);
		}
		else if (jsLayer["name"].get<std::string>() == "Gimmick") {
			LoadGimmickLayer(aObjects);
		}
	}
	return true;
}

void MapChips::LoadTilesets(picojson::object jsRoot,std::string folderpath) {
	// 各タイルセット取得
	picojson::array aTileSets = jsRoot["tilesets"].get<picojson::array>();
	for (int i = 0; i < aTileSets.size(); ++i) {
		picojson::object jsTile = aTileSets[i].get<picojson::object>();
		_tilesetsFirstgid.push_back((int)jsTile["firstgid"].get<double>());
		_chipCount = (int)jsTile["tilecount"].get<double>();

		_chipCount_W = (int)jsTile["columns"].get<double>();
		//_chipCount_H = (_chipCount / _chipCount_W);		// 計算で出す

		_chipSize_W = (int)jsRoot["tilewidth"].get<double>();
		_chipSize_H = (int)jsRoot["tileheight"].get<double>();
		auto a = (int)jsTile["imageheight"].get<double>();
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
		std::vector<bool> tiles_col;
		//tiles_col.push_back(0);
		picojson::array  tiles = jsTile["tiles"].get<picojson::array>();
		for (auto i = tiles.begin(); i != tiles.end(); ++i) {
		bool atile_col{ false };
			/*各クラスgid読み込み*/
			if ((*i).get<picojson::object>()["class"].is<std::string>()) {

				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Enemy") {
					_gidEnemy.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back()));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "EnemyB") {
					St::EnemyBData data;
					data.LookTime.resize(4);
					std::fill(data.LookTime.begin(), data.LookTime.end(), 0);
					data.Direction.resize(4);
					std::fill(data.Direction.begin(), data.Direction.end(), 0);
					data.ID=static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
					data.StartPosition = { 0,0 };
					if ((*i).get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = (*i).get<picojson::object>()["properties"].get<picojson::array>();
						for (int i2 = 0; i2 < properties.size(); ++i2) {
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction1") {
								data.Direction[0] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction2") {
								data.Direction[1] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction3") {
								data.Direction[2] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction4") {
								data.Direction[3] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "LookTime1") {
								data.Direction[0] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "LookTime12") {
								data.Direction[1] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "LookTime13") {
								data.Direction[2] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "LookTime14") {
								data.Direction[3] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
						}
					
					}
					_gidEnemyB.push_back(data);
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Barrier") {
					int player{ 1 };
					if ((*i).get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = (*i).get<picojson::object>()["properties"].get<picojson::array>();
						for (int i2 = 0; i2 < properties.size(); ++i2) {
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Player") {
								player = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
						}
					}
					if (player == 1) {
						_gidBarrier1.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back()));
					}
					else {
						_gidBarrier2.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back()));
					}
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "ItemAmmo") {
					_gidItemAmmo.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back()));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "ItemHP") {
					_gidItemHP.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back()));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Player") {
					_gidPlayer.push_back(static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back()));
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Server") {
					std::string direction = "up";
					bool upperleft = false;
					if ((*i).get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = (*i).get<picojson::object>()["properties"].get<picojson::array>();
						for (int i2 = 0; i2 < properties.size();++i2) {
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction") {
								direction = properties[i2].get<picojson::object>()["value"].get<std::string>();
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "upperleft") {
								upperleft = properties[i2].get<picojson::object>()["value"].get<bool>();
							}
						}
					}
					if (upperleft == true) {
						auto gid = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
						_gidServer.push_back({ gid,direction, });
					}
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Light") {
					SquareLight::SquareLightStats stats;
					stats.image = "resource/Light/Light_square.png";
					stats.activate = 1;
					stats.alpha = 100;
					stats.pos = { 0,0 };
					stats.size = { 100,100 };
					stats.r = 255,
					stats.g = 255;
					stats.b = 255;
					/*id*/
					auto id = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());

					if ((*i).get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = (*i).get<picojson::object>()["properties"].get<picojson::array>();
						for (int i = 0; i < properties.size(); ++i) {
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Activate") {
								stats.activate = properties[i].get<picojson::object>()["value"].get<bool>();
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Color : A") {
								stats.alpha = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Color : B") {
								stats.b = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Color : G") {
								stats.g = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Color : R") {
								stats.r = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Image") {
								stats.image = properties[i].get<picojson::object>()["value"].get<std::string>();
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Size_X") {
								stats.size.x = properties[i].get<picojson::object>()["value"].get<double>();
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Size_Y") {
								stats.size.y = properties[i].get<picojson::object>()["value"].get<double>();
							}
						}
					}
					_gidLight.push_back({ id,stats });
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Teleport_IN") {
					bool randamFlag{0};
					if ((*i).get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = (*i).get<picojson::object>()["properties"].get<picojson::array>();
						for (int i = 0; i < properties.size(); ++i) {
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Random") {
								randamFlag = properties[i].get<picojson::object>()["value"].get<bool>();
							}
						}
					}
					auto id = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
					_gidteleportIn[id] = randamFlag;
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Teleport_OUT") {
					bool randamFlag{ 0 };
					if ((*i).get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = (*i).get<picojson::object>()["properties"].get<picojson::array>();
						for (int i = 0; i < properties.size(); ++i) {
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "RandomPort") {
								randamFlag = properties[i].get<picojson::object>()["value"].get<bool>();
							}
						}
					}
					auto id = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
					_gidteleportOut[id] = randamFlag;
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Switch") {
					auto id = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
					_gidSwitch.push_back(id);
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Door") {
					auto id = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
					_gidDoor.push_back(id);
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "TNT") {
					auto id = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
					_gidTNT.push_back(id);
				}
				if ((*i).get<picojson::object>()["class"].get<std::string>() == "Mine") {
					auto id = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
					_gidMine.push_back(id);
				}
			}
			// チップコリジョンデータ読み込み
			if ((*i).get<picojson::object>()["properties"].is<picojson::array>()) {
				auto properties = (*i).get<picojson::object>()["properties"].get<picojson::array>();
				for (int i2 = 0; i2 < properties.size(); ++i2) {
					if (properties[i2].get<picojson::object>()["name"].is<std::string>()) {
						if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Collision") {
							atile_col = (properties[i2].get<picojson::object>()["value"].get<bool>());
						}
						if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "FrontRender") {
							if (properties[i2].get<picojson::object>()["value"].get<bool>()) {
								auto id = static_cast<int>((*i).get<picojson::object>()["id"].get<double>() + _tilesetsFirstgid.back());
								_gidFront.push_back(id);
							}
						}
					}
				}
			}

			tiles_col.push_back(atile_col);
		}
		_chipCollision.push_back(tiles_col);

	}
	std::sort(_tilesetsFirstgid.begin(), _tilesetsFirstgid.end());
}

void MapChips::LoadTileLayer(picojson::object jsLayer) {
	picojson::array aData = jsLayer["data"].get<picojson::array>();			// マップ配列
	int index = 0;
	std::vector<std::vector<int>>	vMapLayer;	// 1レイヤー分のデータ
	std::vector<std::vector<int>>	vFrontMapLayer;	// 1レイヤー分の手前用データ
	for (int y = 0; y < _mapSize_H; y++) {
		std::vector<int>	vMapLine;	// 1行分のデータ
		std::vector<int>	vFrontMapLine;	// 1行分の手前データ
		for (int x = 0; x < _mapSize_W; x++) {
			int chip_id;
			chip_id = (int)aData[index].get<double>();
			vMapLine.push_back(chip_id);

			if (_gidFront.size() == 0) {
				vFrontMapLine.push_back(-1);
			}
			for (int i = 0; i < _gidFront.size();++i) {
				if (chip_id == _gidFront[i]) {
					vFrontMapLine.push_back(chip_id);
					break;
				}
				if (i==_gidFront.size()-1) {
					vFrontMapLine.push_back(-1);
					break;
				}
			}

			index++;
		}
		vMapLayer.push_back(vMapLine);
		vFrontMapLayer.push_back(vFrontMapLine);
	}
	// レイヤーデータを追加
	_mapTileData.push_back(vMapLayer);
	_mapFrontTileData.push_back(vFrontMapLayer);
}

void MapChips::LoadMiniMapLayer(picojson::array aObjects) {
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
		if (linestyle != "NULL") {
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
			_minimapData.push_back(polygonplots);
		}
	}
}

void MapChips::LoadPlayerLayer(picojson::array aObjects) {
	/*各オブジェクトの判定*/
	for (int i = 0; i < aObjects.size(); ++i) {
		/*各オブジェクトのgidがタイルセット上でプレイヤークラスに設定されている物か*/
		for (auto gid : _gidPlayer) {
			if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid) {
				auto properties=aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
				/*カスタムプロパティ0番目にPlayerの項目があるか*/
				if (properties[0].get<picojson::object>()["name"].get<std::string>() == "Player") {
					int playerno = static_cast<int>(properties[0].get<picojson::object>()["value"].get<double>());
					double posX = aObjects[i].get<picojson::object>()["x"].get<double>();
					double posY = aObjects[i].get<picojson::object>()["y"].get<double>();
					_playerStart[playerno] = { posX,posY };
				}
			}
		}
	}
}

void MapChips::LoadItemLayer(picojson::array aObjects) {
	for (int i = 0; i < aObjects.size(); ++i) {
		double posX, posY;
		for (auto gid : _gidItemAmmo) {
			if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid) {
				posX = aObjects[i].get<picojson::object>()["x"].get<double>();
				posY = aObjects[i].get<picojson::object>()["y"].get<double>();
				_bulletItems.push_back({posX,posY});
			}
		}
		for (auto gid : _gidItemHP) {
			if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid) {
				posX = aObjects[i].get<picojson::object>()["x"].get<double>();
				posY = aObjects[i].get<picojson::object>()["y"].get<double>();
				_hpItems.push_back({posX,posY});
			}
		}
	}
}

void MapChips::LoadEnemyLayer(picojson::array aObjects) {
	for (int i = 0; i < aObjects.size(); ++i) {
		/*gidを持っている場合エネミーを示す可能性がある*/
		if (aObjects[i].get<picojson::object>()["gid"].is<double>()) {
			for (auto gid : _gidEnemy) {
				/*各オブジェクトのgidがタイルセット上でエネミークラスに設定されている物か判定*/
				if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid) {

					int aEnemyID;
					int     aWaitFrame{0};
					Vector2	aEnemyPosition;
					int aPatrolID{-1};

					if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>()) {
						picojson::array properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
						for (int i2 = 0; i2 < properties.size(); ++i2) {
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "WaitFrame") {
								aWaitFrame = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "PatrolLine") {
								aPatrolID = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
						}
					}
					aEnemyID = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
					double posX = aObjects[i].get<picojson::object>()["x"].get<double>();
					double posY = aObjects[i].get<picojson::object>()["y"].get<double>();
					aEnemyPosition = { posX,posY };
					_enemyDataList.push_back({ aEnemyID, aEnemyPosition, aPatrolID,aWaitFrame });
				}
			}
			for (auto gid : _gidEnemyB) 
			{
				/*各オブジェクトのgidがタイルセット上でエネミーBクラスに設定されている物か判定*/
				if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid.ID) {
					St::EnemyBData data =gid;
					data.ID = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
					data.StartPosition.x = aObjects[i].get<picojson::object>()["x"].get<double>();
					data.StartPosition.y = aObjects[i].get<picojson::object>()["y"].get<double>();
					if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
						for (int i2 = 0; i2 < properties.size(); ++i2) {
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction1") {
								data.Direction[0] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction2") {
								data.Direction[1] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction3") {
								data.Direction[2] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "Direction4") {
								data.Direction[3] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "LookTime1") {
								data.LookTime[0] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "LookTime2") {
								data.LookTime[1] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "LookTime3") {
								data.LookTime[2] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "LookTime4") {
								data.LookTime[3] = static_cast<int>(properties[i2].get<picojson::object>()["value"].get<double>());
							}
						}
					}
					_enemyBDataList.push_back(data);
				}
			}
		}
		/*polygonかpolylineがあれば巡回経路情報を示す*/
		else if (aObjects[i].get<picojson::object>()["polygon"].is<picojson::array>() ||
			aObjects[i].get<picojson::object>()["polyline"].is<picojson::array>()) {
			/*敵1体分の巡回ルート*/
			St::EnemyPatrol aPatrolData;
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
			/*最初の点のワールド座標位置*/
			double rootX = aObjects[i].get<picojson::object>()["x"].get<double>();
			double rootY = aObjects[i].get<picojson::object>()["y"].get<double>();
			picojson::array pointsArray = aObjects[i].get<picojson::object>()[linestyle].get<picojson::array>();
			for (int p = 0; p < pointsArray.size(); ++p)
			{
				double x = rootX + pointsArray[p].get <picojson::object>()["x"].get<double>();
				double y = rootY + pointsArray[p].get <picojson::object>()["y"].get<double>();

				aPatrolData.PatrolPoints.push_back({x,y});
			}
			/*巡回経路に割り振られたID読み込み*/
			int id = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
			aPatrolData.ID = id;
			/*mapにIDをキーとして巡回ルート登録*/
			_patrolPoints[id] = aPatrolData;
		}
	}
}

void MapChips::LoadLightLayer(picojson::array aObjects) {
	for (int i = 0; i < aObjects.size(); ++i) {
		if (aObjects[i].get<picojson::object>()["gid"].is<double>()) {
			for (auto gid : _gidLight) {
				if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid.first) {
					auto stats =gid.second;
					if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
						for (int i = 0; i < properties.size(); ++i) {
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Activate") {
								stats.activate = properties[i].get<picojson::object>()["value"].get<bool>();
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Color : A") {
								stats.alpha = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Color : B") {
								stats.b = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Color : G") {
								stats.g = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Color : R") {
								stats.r = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Image") {
								stats.image = properties[i].get<picojson::object>()["value"].get<std::string>();
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Size_X") {
								stats.size.x = properties[i].get<picojson::object>()["value"].get<double>();
							}
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Size_Y") {
								stats.size.y = properties[i].get<picojson::object>()["value"].get<double>();
							}
						}
					}
					stats.pos = { aObjects[i].get<picojson::object>()["x"].get<double>()-(stats.size.x/2),
						aObjects[i].get<picojson::object>()["y"].get<double>()-(stats.size.y / 2) };
					int id = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
					_lightDataList.push_back({ id,stats });
				}
			}
		}
	};
}

void MapChips::LoadServerLayer(picojson::array aObjects) {
	for (int i = 0; i < aObjects.size(); ++i) {
		/*マップタイル3番はエネミー*/
		if (aObjects[i].get<picojson::object>()["gid"].is<double>()) {
			for(auto gid:_gidServer) {
				if (aObjects[i].get<picojson::object>()["gid"].get<double>() == gid.gid) {
					/*残りはサーバーのデータ*/
					Vector2 pos{ 0,0 };
					std::string dir{ gid.Direction };
					bool upperleft{ true };
					if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>())
					{
						picojson::array properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
						for (int i2 = 0; i2 < properties.size(); ++i2) {
							if (properties[i2].get<picojson::object>()["name"].get<std::string>() == "upperleft") {
								upperleft = properties[i2].get<picojson::object>()["value"].get<bool>();
							}
							if (properties[i2].get<picojson::object>()["name"].get<std::string>()=="Direction") {
								dir = properties[i2].get<picojson::object>()["value"].get<std::string>();
							}
						}
					}
					if (upperleft == true ){
						pos.x = aObjects[i].get<picojson::object>()["x"].get<double>();
						pos.y = aObjects[i].get<picojson::object>()["y"].get<double>();
						_serverMachineDataList.push_back({ pos,dir });
					}
				}
			}
		}
		/*height=0はPolylineかpolygonによる巡回ルートオブジェクト*/
		if (aObjects[i].get<picojson::object>()["polygon"].is<picojson::array>() ||
			aObjects[i].get<picojson::object>()["polyline"].is<picojson::array>()) {
			/*敵1体分の巡回ルート*/
			St::EnemyPatrol aPatrolData;
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
}

void MapChips::LoadGimmickLayer(picojson::array aObjects) {
	for (int i = 0; i < aObjects.size(); ++i) {
		/*テレポーター入口読み込み*/
		if (aObjects[i].get<picojson::object>()["gid"].is<double>()) {
			auto gid = static_cast<int>(aObjects[i].get<picojson::object>()["gid"].get<double>());
			if (_gidteleportIn.find(gid) != _gidteleportIn.end()) {
				ObjectDataStructs::teleporterData stat;
				stat.random = _gidteleportIn[gid];
				stat.tereortID = -1;
				stat.pos.x = aObjects[i].get<picojson::object>()["x"].get<double>();
				stat.pos.y = aObjects[i].get<picojson::object>()["y"].get<double>();
				if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>()) {
					auto properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
					for (int i = 0; i < properties.size(); ++i) {
						if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Random") {
							stat.random = properties[i].get<picojson::object>()["value"].get<bool>();
						}
						if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Teleport_OUT") {
							stat.tereortID = static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>());
						}
					}
				}
				if (stat.random == true || stat.tereortID != -1) {

					_teleporterInDataList.push_back(stat);
				}
			}
			/*テレポーター出口読み込み*/
			if (_gidteleportOut.find(gid) != _gidteleportOut.end()) {
				bool randomflag{0};
				Vector2 pos;
				pos.x = aObjects[i].get<picojson::object>()["x"].get<double>();
				pos.y = aObjects[i].get<picojson::object>()["y"].get<double>();
				if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>()) {
					auto properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
					for (int i = 0; i < properties.size(); ++i) {
						if (properties[i].get<picojson::object>()["name"].get<std::string>() == "RandomPort") {
							randomflag = properties[i].get<picojson::object>()["value"].get<bool>();
						}
					}
				}
				auto id = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
				_teleporterOutDataList[id] = { pos,randomflag };
			}
			/*スイッチ読み込み*/
			for (auto gid : _gidSwitch) {
				if (gid == static_cast<int>(aObjects[i].get<picojson::object>()["gid"].get<double>())) {
					St::SwitchData data;
					if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
						for (int i = 0; i < properties.size(); ++i) {
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "LinkGimmick1"||
								properties[i].get<picojson::object>()["name"].get<std::string>() == "LinkGimmick2" ||
								properties[i].get<picojson::object>()["name"].get<std::string>() == "LinkGimmick3" ||
								properties[i].get<picojson::object>()["name"].get<std::string>() == "LinkGimmick4" ||
								properties[i].get<picojson::object>()["name"].get<std::string>() == "LinkGimmick5") {
								data.links.push_back(static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>()));
							}
						}
					}
					if (data.links.size() != 0) {

						data.pos.x = aObjects[i].get<picojson::object>()["x"].get<double>();
						data.pos.y = aObjects[i].get<picojson::object>()["y"].get<double>();
						data.ID = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
						_switchDataList.push_back(data);
					}
				}
			}
			for (auto gid : _gidDoor) {
				if (gid == static_cast<int>(aObjects[i].get<picojson::object>()["gid"].get<double>())) {
					Vector2 pos;
					pos.x = static_cast<int>(aObjects[i].get<picojson::object>()["x"].get<double>());
					pos.y = static_cast<int>(aObjects[i].get<picojson::object>()["y"].get<double>());
					auto id = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
					_doorDataList.push_back({ id, pos });
				}
			}
			for (auto gid : _gidTNT) {
				if (gid == static_cast<int>(aObjects[i].get<picojson::object>()["gid"].get<double>())) {
					Vector2 pos;
					pos.x = static_cast<int>(aObjects[i].get<picojson::object>()["x"].get<double>());
					pos.y = static_cast<int>(aObjects[i].get<picojson::object>()["y"].get<double>());
					auto id = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
					_tNTDataList.push_back({ id, pos });
				}
			}
			for (auto gid : _gidMine) {
				if (gid == static_cast<int>(aObjects[i].get<picojson::object>()["gid"].get<double>())) {
					St::MineData data;
					data.pos.x = static_cast<int>(aObjects[i].get<picojson::object>()["x"].get<double>());
					data.pos.y = static_cast<int>(aObjects[i].get<picojson::object>()["y"].get<double>());
					data.ID = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
					std::string direction{ "none" };
					if (aObjects[i].get<picojson::object>()["properties"].is<picojson::array>()) {
						auto properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();
						for (int i = 0; i < properties.size(); ++i) {
							if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Direction"){
								direction = properties[i].get<picojson::object>()["value"].get<std::string>();
							}
						}
					}
					if (direction == "up") {
						data.dir = 4;
					}
					else if (direction == "down") {
						data.dir = 2;

					}
					else if (direction == "right") {

						data.dir = 1;
					}
					else if (direction == "left") {
						data.dir = 3;
					}
					else {
						data.dir = -1;
					}

					_mineDataList.push_back(data);
				}
			}
		}
	}
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
	for (int layer = 0; layer < _mapTileData.size(); ++layer)
	{
		for (y = 0; y < _mapSize_H; ++y)
		{
			for(x = 0 ; x < _mapSize_W ; ++x)
			{
				int layerstart = _mapSize_W * _mapSize_H * layer;
				int index = y * _mapSize_W + x;
				int pos_x = x * _chipSize_W +static_cast<int>(windowPos.x) - static_cast<int>(cameraPos.x);
				int pos_y = y * _chipSize_H + static_cast<int>(windowPos.y) - static_cast<int>(cameraPos.y);
				int chip_no = _mapTileData[layer][y][x];
				chip_no--;
				int chiplayer = 0;
				for (int i = static_cast<int>(_cgChip.size()) - 1; 0 <= i; --i) {
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
	for (int i = 0; i < _minimapData.size(); ++i)
	{
		int plotsize = static_cast<int>(_minimapData[i].size());
		for (int plot = 0; plot < plotsize; ++plot) 
		{
			//float scale =static_cast<float>( 410.0/3240.0*0.97);
			float scale = static_cast<float>(410.0 / 4320.0 * 0.97);
			DrawLineAA(static_cast<float>(_minimapData[i][plot].x*scale + windowPos.x),
				static_cast<float>(_minimapData[i][plot].y*scale + windowPos.y ),
				static_cast<float>(_minimapData[i][(plot + 1) % plotsize].x *scale+ windowPos.x),
				static_cast<float>(_minimapData[i][(plot + 1) % plotsize].y *scale+ windowPos.y ),
				GetColor(0, 255, 255));
		}
	}
}

void MapChips::FrontRender(int stageNum, Vector2 windowPos, Vector2 cameraPos) {
	int x, y;
	for (int layer = 0; layer < _mapFrontTileData.size(); ++layer)
	{
		for (y = 0; y < _mapSize_H; ++y)
		{
			for (x = 0; x < _mapSize_W; ++x)
			{
				int layerstart = _mapSize_W * _mapSize_H * layer;
				int index = y * _mapSize_W + x;
				int pos_x = x * _chipSize_W + static_cast<int>(windowPos.x) - static_cast<int>(cameraPos.x);
				int pos_y = y * _chipSize_H + static_cast<int>(windowPos.y) - static_cast<int>(cameraPos.y);
				int chip_no = _mapFrontTileData[layer][y][x];
				if (chip_no != -1) {
					chip_no--;
					int chiplayer = 0;
					for (int i = static_cast<int>(_cgChip.size()) - 1; 0 <= i; --i) {
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
	v_chip_no.resize(0);
	// マップチップ位置はマップデータからはみ出ているか？
	if (0 <= x && x < _mapSize_W && 0 <= y && y < _mapSize_H)
	{	
		// マップチップIDが0以外は当たり判定を行う
		for( int layer = 0; layer < _mapTileData.size(); ++layer) {
			int chip_no = _mapTileData[layer][y][x];
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
			for (int i = 0; i < v_chip_no.size(); ++i) {
				int chip_no=v_chip_no[i];
				int tileset=0;
				for (int i2 = static_cast<int>(_tilesetsFirstgid.size()) - 1; i2 >= 0; --i2) {
					if (chip_no>=_tilesetsFirstgid[i2]) {
						chip_no = chip_no- _tilesetsFirstgid[i2];
						tileset = i2;
						break;
					}
				}
				if (chip_no != -1) {
					if (_chipCollision[tileset][chip_no]) {
						return 1;
					}
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
					for (auto gid : _gidBarrier1) {
						if (chip_no == gid)
						{	// このチップと当たった。
							// 当たったので戻る
							return 1;
						}
					}
				}
				if (playerno == 1) {
					for (auto gid : _gidBarrier2) {
						if (chip_no == gid)
						{	// このチップと当たった。
							// 当たったので戻る
							return 1;
						}
					}
				}
			}
		}
	}
	// 当たらなかった
	return 0;
}

ObjectDataStructs::EnemyPatrol MapChips::FindPatrol(int id){
	auto points = _patrolPoints.find(id);
	if (points != _patrolPoints.end()) {
		return points->second;
	}

	return {-1, { {0,0} }, false };
}

Vector2 MapChips::GetPlayerStartPosition(int playerno) {
	if (_playerStart.find(playerno + 1) != _playerStart.end()) {
		return _playerStart[playerno + 1];
	}
	return { 0,0 };
}