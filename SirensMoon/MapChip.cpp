#include"MapChip.h"
#include "Camera.h"
#include "ImageServer.h"

MapChip::MapChip(Game& game, ModeBase& mode, std::string filename) :_game{ game }, _mode{ mode }{
	_mapTileData.clear();
	_minimapData.clear();
	LoadMap("resource/MapData/", filename);
}

MapChip::~MapChip() {
}

bool MapChip::LoadMap(std::string folderpath, std::string filename)
{

	// ファイルからjsonデータの読み込み
	std::ifstream ifs(folderpath + filename);
	picojson::value json;
	ifs >> json;

	// jsonデータからパラメータを取得
	picojson::object jsRoot = json.get<picojson::object>();
	_mapSize_W = (int)jsRoot["width"].get<double>();
	_mapSize_H = (int)jsRoot["height"].get<double>();

	LoadTilesets(jsRoot, folderpath);

	// レイヤー情報の取得
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();

	for (int i = 0; i < aLayers.size(); i++)
	{

		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// レイヤーオブジェクト


		// レイヤー種類が「タイルレイヤー」のものを読み込み
		if (jsLayer["type"].get<std::string>() == "tilelayer")
		{
			LoadTileLayer(jsLayer);
		}
		// レイヤー種類が「オブジェクトレイヤー」のものを読み込み
		if (jsLayer["type"].get<std::string>() == "objectgroup") {
			/*オブジェクトレイヤーに存在するオブジェクト配列*/
			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			for (int i = 0; i < aObjects.size(); ++i) {
				picojson::object aObject = aObjects[i].get<picojson::object>();
				/*オブジェクトがgidを所有しているか確認*/
				if (!aObject["gid"].is<double>()) {
					continue;
				}
				int gid = static_cast<int>(aObject["gid"].get<double>());
				/*タイルセット上でクラス設定されている物か確認*/
				if (_objectGIDs.count(gid) == 0) {
					continue;
				}
				/*基本データ読み込み*/
				std::unique_ptr<ObjectDataBase>& data = _objectGIDs[gid];
				SetBasicObjectData(aObject, data);
				/*クラス別データ読み込み*/
				if (data->GetType() == ObjectDataBase::Type::Player) {
					auto&& playerData = static_cast<PlayerData&>(*data);
					LoadPlayerClass(aObject, playerData);
				}
				else if (data->GetType() == ObjectDataBase::Type::Enemy) {
					if (aObject["class"].get<std::string>() == "EnemyB") {
						EnemyBData enemyBData;
						enemyBData.pos = data->pos;
						enemyBData.ID = data->ID;
						enemyBData.sightH = static_cast<EnemyData&>(*data).sightH;
						enemyBData.sightW = static_cast<EnemyData&>(*data).sightW;
						enemyBData.detectionComplete = static_cast<EnemyData&>(*data).detectionComplete;
						LoadEnemyBClass(aObject, enemyBData);
					}
					else {
						auto&& enemyData = static_cast<EnemyData&>(*data);
						LoadEnemyClass(aObject, enemyData);
					}
				}
				else if (data->GetType() == ObjectDataBase::Type::EnemyB) {
					if (aObject["class"].get<std::string>() == "Enemy") {
						EnemyData enemyData;
						enemyData.pos = data->pos;
						enemyData.ID = data->ID;
						enemyData.sightH = static_cast<EnemyBData&>(*data).sightH;
						enemyData.sightW = static_cast<EnemyBData&>(*data).sightW;
						enemyData.detectionComplete = static_cast<EnemyBData&>(*data).detectionComplete;
						LoadEnemyClass(aObject, enemyData);
					}
					else {
						auto&& enemyBData = static_cast<EnemyBData&>(*data);
						LoadEnemyBClass(aObject, enemyBData);
					}
				}
				else if (data->GetType() == ObjectDataBase::Type::Door) {
					auto&& doorData = static_cast<DoorData&>(*data);
					LoadDoorClass(aObject, doorData);
				}
				else if (data->GetType() == ObjectDataBase::Type::AmmoItem) {
					auto&& ammoData = static_cast<BulletItemData&>(*data);
					LoadItemAmmoClass(aObject, ammoData);
				}
				else if (data->GetType() == ObjectDataBase::Type::HPItem) {
					auto&& hpData = static_cast<HPItemData&>(*data);
					LoadItemHPClass(aObject, hpData);
				}
				else if (data->GetType() == ObjectDataBase::Type::Light) {
					auto&& lightData = static_cast<SquareLightStats&>(*data);
					LoadLightClass(aObject, lightData);
				}
				else if (data->GetType() == ObjectDataBase::Type::Mine) {
					auto&& mineData = static_cast<MineData&>(*data);
					LoadMineClass(aObject, mineData);
				}
				else if (data->GetType() == ObjectDataBase::Type::ScreenPump) {
					auto&& screenData = static_cast<ScreenPumpData&>(*data);
					LoadScreenPumpClass(aObject, screenData);
				}
				else if (data->GetType() == ObjectDataBase::Type::Server) {
					auto&& serverData = static_cast<ServerMachineData&>(*data);
					LoadServerClass(aObject, serverData);
				}
				else if (data->GetType() == ObjectDataBase::Type::StickeyBomb) {
					auto&& stickyData = static_cast<StickyBombData&>(*data);
					LoadStickyBombClass(aObject, stickyData);
				}
				else if (data->GetType() == ObjectDataBase::Type::Switch) {
					auto&& switchData = static_cast<SwitchData&>(*data);
					LoadSwitchClass(aObject, switchData);
				}
				else if (data->GetType() == ObjectDataBase::Type::SwitchArea) {
					auto&& switchAreaData = static_cast<SwitchAreaData&>(*data);
					LoadSwitchAreaClass(aObject, switchAreaData);
				}
				else if (data->GetType() == ObjectDataBase::Type::Teleport_IN) {
					auto&& teleprtInData = static_cast<teleporterData&>(*data);
					LoadTeleport_INClass(aObject, teleprtInData);
				}
				else if (data->GetType() == ObjectDataBase::Type::Teleport_OUT) {
					auto&& teleprtOutData = static_cast<TeleporterOutData&>(*data);
					LoadTeleport_OUTClass(aObject, teleprtOutData);
				}
				else if (data->GetType() == ObjectDataBase::Type::TNT) {
					auto&& tntData = static_cast<TNTData&>(*data);
					LoadTNTClass(aObject, tntData);
				}
				else if (data->GetType() == ObjectDataBase::Type::Barrirer) {
					auto&& barrierData = static_cast<BarrierData&>(*data);
					LoadBarrierClass(aObject, barrierData);
				}
				else if (data->GetType() == ObjectDataBase::Type::BossGenerator) {
					auto&& bigGenData = static_cast<BigGeneratorData&>(*data);
					LoadBossGeneratorClass(aObject, bigGenData);
				}
				else if (data->GetType() == ObjectDataBase::Type::BossRailGun) {
					auto&& bigGunData = static_cast<BigGunData&>(*data);
					LoadBossRailGunClass(aObject, bigGunData);
				}
				else if (data->GetType() == ObjectDataBase::Type::BossServer) {
					auto&& bigServerData = static_cast<BigServerData&>(*data);
					LoadBossServerClass(aObject, bigServerData);
				}
				else if (data->GetType() == ObjectDataBase::Type::BossTrigger) {
					auto&& trrigerData = static_cast<BossGimmickControllerData&>(*data);
					LoadBossTriggerClass(aObject, trrigerData);
				}
				else if (data->GetType() == ObjectDataBase::Type::BreakableObject) {
					auto&& breakData = static_cast<BreakableObjectData&>(*data);
					LoadBreakableObjectClass(aObject, breakData);
				}
				else if (data->GetType() == ObjectDataBase::Type::DigitalLetter) {
					auto&& letterData = static_cast<DigitalLetterData&>(*data);
					LoadDigitalLetterClass(aObject, letterData);
				}
			}
			if (jsLayer["name"].get<std::string>() == "MiniMap")
			{
				LoadMiniMapLayer(aObjects);
			}
			else if (jsLayer["name"].get<std::string>() == "Enemy")
			{
				LoadEnemyPatrolLine(aObjects);
			}
			else if (jsLayer["name"].get<std::string>() == "Server") {
				LoadEnemyVIPPatrolLine(aObjects);
			}
		}
	}
	return true;
}

void MapChip::LoadTilesets(picojson::object jsRoot, std::string folderpath) {
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

		picojson::array  tiles = jsTile["tiles"].get<picojson::array>();
		for (auto i2 = tiles.begin(); i2 != tiles.end(); ++i2) {
			picojson::object tileObject = (*i2).get<picojson::object>();
			/*各タイルに設定されているデータをgidに紐付けて読み込み*/
			if (tileObject["class"].is<std::string>()) {
				if (tileObject["class"].get<std::string>() == "Enemy") {
					int gid = (static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back()));
					auto data = std::make_unique<EnemyData>();
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->waitFrame, properties, "WaitFrame");
						FindPropertieData(data->detectionComplete, properties, "FindTime");
						FindPropertieData(data->sightH, properties, "Sight_H");
						FindPropertieData(data->sightW, properties, "Sight_W");
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "EnemyB") {
					std::vector<int> v_zero;
					v_zero.resize(4);
					std::fill(v_zero.begin(), v_zero.end(), 0);
					auto data = std::make_unique<EnemyBData>();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					data->pos = { 0,0 };
					data->Direction = v_zero;
					data->LookTime = v_zero;
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->Direction[0], properties, "Direction1");
						FindPropertieData(data->Direction[1], properties, "Direction2");
						FindPropertieData(data->Direction[2], properties, "Direction3");
						FindPropertieData(data->Direction[3], properties, "Direction4");
						FindPropertieData(data->LookTime[0], properties, "LookTime1");
						FindPropertieData(data->LookTime[1], properties, "LookTime2");
						FindPropertieData(data->LookTime[2], properties, "LookTime3");
						FindPropertieData(data->LookTime[3], properties, "LookTime4");
						FindPropertieData(data->detectionComplete, properties, "FindTime");
						FindPropertieData(data->sightH, properties, "Sight_H");
						FindPropertieData(data->sightW, properties, "Sight_W");
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "Barrier") {
					auto data = std::make_unique< BarrierData>();
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						for (int i3 = 0; i3 < properties.size(); ++i3) {
							picojson::object aPropetie = properties[i3].get<picojson::object>();
							if (aPropetie["name"].get<std::string>() == "Player") {
								data->blockPlayerNo = static_cast<int>(aPropetie["value"].get<double>());
							}
						}
					}
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					if (data->blockPlayerNo == 1) {
						_gidBarrier1.push_back(gid);
					}
					else if (data->blockPlayerNo == 2) {
						_gidBarrier2.push_back(gid);
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "ItemAmmo") {
					auto data = std::make_unique< BulletItemData>();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "ItemHP") {
					auto data = std::make_unique< HPItemData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "Player") {
					auto data = std::make_unique< PlayerData >();
					if (tileObject["properties"].is<picojson::array>()) {
						auto properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->Player, properties, "Player");
						FindPropertieData(data->Accelerate, properties, "Accelerate");
						FindPropertieData(data->Friction, properties, "Friction");
						FindPropertieData(data->SpeedMax, properties, "SpeedMax");
						FindPropertieData(data->SlowSpeedRate, properties, "ChargeWalkRate");

					}
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "Server") {
					auto data = std::make_unique <ServerMachineData>();
					if (tileObject["properties"].is<picojson::array>()) {
						auto properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->Direction, properties, "Direction");
						std::wstring w_ss = utf8_to_wide(data->Direction);
						data->Direction = wide_to_sjis(w_ss);
						FindPropertieData(data->upperleft, properties, "upperleft");

					}
					if (data->upperleft) {
						int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
						_objectGIDs[gid] = std::move(data);
					}
				}
				if (tileObject["class"].get<std::string>() == "Light") {
					auto data = std::make_unique< SquareLightStats >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());

					if (tileObject["properties"].is<picojson::array>()) {
						auto properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->activate, properties, "Activate");
						FindPropertieData(data->alpha, properties, "Color : A");
						FindPropertieData(data->b, properties, "Color : B");
						FindPropertieData(data->g, properties, "Color : G");
						FindPropertieData(data->r, properties, "Color : R");
						FindPropertieData(data->object, properties, "ObjectImage");
						std::wstring w_ss = utf8_to_wide(data->object);
						data->object = wide_to_sjis(w_ss);
						FindPropertieData(data->image, properties, "Image");
						std::wstring w_ss2 = utf8_to_wide(data->image);
						data->image = wide_to_sjis(w_ss2);
						FindPropertieData(data->size.x, properties, "Size_X");
						FindPropertieData(data->size.y, properties, "Size_Y");
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "Teleport_IN") {
					auto data = std::make_unique< teleporterData >();
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->random, properties, "Random");
					}
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "Teleport_OUT") {
					auto data = std::make_unique< TeleporterOutData >();
					if (tileObject["properties"].is<picojson::array>()) {
						auto properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->random, properties, "RandomPort");
					}
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "Switch") {
					auto data = std::make_unique< SwitchData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->RedFlag, properties, "Red?");
						FindPropertieData(data->projectionNumber, properties, "EffectNumber");
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "SwitchArea") {
					auto data = std::make_unique< SwitchAreaData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->Reverse, properties, "Reverse");
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "Door") {
					auto data = std::make_unique< DoorData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->PartNo, properties, "PartNo");
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "TNT") {
					auto data = std::make_unique<TNTData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					if (tileObject["properties"].is<picojson::array>()) {
						auto properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->CG, properties, "CGNo");
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "Mine") {
					auto data = std::make_unique< MineData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->range, properties, "Range");
						std::string direction;
						FindPropertieData(direction, properties, "Direction");
						if (direction == "up") {
							data->dir = 4;
						}
						else if (direction == "down") {
							data->dir = 2;
						}
						else if (direction == "right") {
							data->dir = 1;
						}
						else if (direction == "left") {
							data->dir = 3;
						}
						else {
							data->dir = -1;
						}
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "ScreenPump") {
					auto data = std::make_unique< ScreenPumpData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					if (tileObject["properties"].is<picojson::array>()) {
						auto properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->range, properties, "Range");
						std::string direction{ "none" };
						FindPropertieData(direction, properties, "Direction");
						if (direction == "up") {
							data->dir = 4;
						}
						else if (direction == "down") {
							data->dir = 2;
						}
						else if (direction == "right") {
							data->dir = 1;
						}
						else if (direction == "left") {
							data->dir = 3;
						}
						else {
							data->dir = -1;
						}
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "StickyBomb") {
					auto data = std::make_unique< StickyBombData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					if (tileObject["properties"].is<picojson::array>()) {
						picojson::array properties = tileObject["properties"].get<picojson::array>();
						FindPropertieData(data->range, properties, "Range");
						FindPropertieData(data->timer, properties, "Timer");
					}
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "BreakableObject") {
					auto data = std::make_unique< BreakableObjectData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "DegitalLetter") {
					auto data = std::make_unique< DigitalLetterData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "BossGenerator") {
					auto data = std::make_unique< BigGeneratorData >();
					int gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "BossRailGun") {
					auto data = std::make_unique< BigGunData >();
					auto gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "BossServer") {
					auto data = std::make_unique< BigServerData >();
					auto gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
				if (tileObject["class"].get<std::string>() == "BossTrigger") {
					auto data = std::make_unique< BossGimmickControllerData >();
					auto gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
					_objectGIDs[gid] = std::move(data);
				}
			}
			// チップコリジョンデータ読み込み
			if (tileObject["class"].get<std::string>() == "BackGround") {
				if (tileObject["properties"].is<picojson::array>()) {
					auto properties = tileObject["properties"].get<picojson::array>();
					for (int i3 = 0; i3 < properties.size(); ++i3) {
						picojson::object aPropetie = properties[i3].get<picojson::object>();
						if (aPropetie["name"].get<std::string>() == "Collision") {
							if (aPropetie["value"].get<bool>()) {
								auto gid = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
								_chipCollision.push_back(gid);
							}
						}
						if (aPropetie["name"].get<std::string>() == "FrontRender") {
							if (aPropetie["value"].get<bool>()) {
								auto id = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
								_gidFront.push_back(id);
							}
						}
						if (aPropetie["name"].get<std::string>() == "BackRender") {
							if (aPropetie["value"].get<bool>()) {
								auto id = static_cast<int>(tileObject["id"].get<double>() + _tilesetsFirstgid.back());
								_gidBack.push_back(id);
							}
						}
					}
				}
			}
		}
	}
	std::sort(_tilesetsFirstgid.begin(), _tilesetsFirstgid.end());
}

void MapChip::LoadTileLayer(picojson::object jsLayer) {
	picojson::array aData = jsLayer["data"].get<picojson::array>();			// マップ配列
	std::vector<std::vector<int>>	vMapLayer;	// 1レイヤー分のデータ
	std::vector<std::vector<int>>	vFrontMapLayer;	// 1レイヤー分の手前用データ
	std::vector<std::vector<int>>	vBackMapLayer;	// 1レイヤー分の奥用データ
	for (int y = 0; y < _mapSize_H; y++) {
		std::vector<int>	vMapLine;	// 1行分のデータ
		std::vector<int>	vFrontMapLine;	// 1行分の手前データ
		std::vector<int>	vBackMapLine;	// 1行分の奥データ
		for (int x = 0; x < _mapSize_W; x++) {
			int chip_id = static_cast<int>(aData[y * _mapSize_W + x].get<double>());
			/*タイルが手前描画設定されているか*/
			if (std::find(_gidFront.begin(), _gidFront.end(), chip_id) != _gidFront.end()) {
				vFrontMapLine.push_back(chip_id);
				vMapLine.push_back(-1);
				vBackMapLine.push_back(-1);
			}
			/*タイルが奥描画設定されているか*/
			else if (std::find(_gidBack.begin(), _gidBack.end(), chip_id) != _gidBack.end()) {
				vFrontMapLine.push_back(-1);
				vMapLine.push_back(-1);
				vBackMapLine.push_back(chip_id);
			}
			else {
				vFrontMapLine.push_back(-1);
				vMapLine.push_back(chip_id);
				vBackMapLine.push_back(-1);
			}
		}
		vMapLayer.push_back(vMapLine);
		vFrontMapLayer.push_back(vFrontMapLine);
		vBackMapLayer.push_back(vBackMapLine);
	}
	// レイヤーデータを追加
	_mapTileData.push_back(vMapLayer);
	_mapFrontTileData.push_back(vFrontMapLayer);
	_mapBackTileData.push_back(vBackMapLayer);
}

void MapChip::LoadMiniMapLayer(picojson::array aObjects) {
	for (int i = 0; i < aObjects.size(); ++i)
	{
		picojson::object aObject = aObjects[i].get<picojson::object>();
		std::string linestyle = "NULL";
		/*polylineが存在するか確認*/

		if (aObject["polyline"].is<picojson::array>()) {
			linestyle = "polyline";
		}
		/*polygonが存在するか確認*/
		else if (aObject["polygon"].is<picojson::array>()) {
			linestyle = "polygon";
		}
		/*一つのポリゴンの頂点データ*/
		std::vector<Vector2> polygonplots;
		if (linestyle != "NULL") {
			int R{ 0 }, G{ 255 }, B{ 255 };
			if (aObject["class"].get<std::string>() == "MiniMapColorLine") {
				if (aObject["properties"].is<picojson::array>()) {
					picojson::array properties = aObject["properties"].get<picojson::array>();
					FindPropertieData(R, properties, "R");
					FindPropertieData(R, properties, "G");
					FindPropertieData(R, properties, "B");
				}
			}
			/*ポリゴンの頂点数分ループ*/
			picojson::array polylineplots = aObject[linestyle].get<picojson::array>();
			for (int i2 = 0; i2 < polylineplots.size(); ++i2)
			{
				auto x = polylineplots[i2].get<picojson::object>()["x"].get<double>()
					+ aObject["x"].get<double>();
				auto y = polylineplots[i2].get<picojson::object>()["y"].get<double>()
					+ aObject["y"].get<double>();
				Vector2 plot = { x,y };
				polygonplots.push_back(plot);
			}
			_minimapData.push_back({ GetColor(R,G,B), polygonplots });
		}
	}
}
void MapChip::LoadEnemyPatrolLine(picojson::array aObjects) {
	for (int i = 0; i < aObjects.size(); ++i) {
		picojson::object aObject = aObjects[i].get<picojson::object>();
		/*polygonかpolylineがあれば巡回経路情報を示す*/
		if (aObject["polygon"].is<picojson::array>() ||
			aObject["polyline"].is<picojson::array>()) {
			/*敵1体分の巡回ルート*/
			EnemyPatrol aPatrolData;
			std::string linestyle = "null";
			/*polylineが存在するか確認*/
			if (aObject["polyline"].is<picojson::array>()) {
				linestyle = "polyline";
				aPatrolData.TruckingMode = 0;
			}
			/*polygonが存在するか確認*/
			else if (aObject["polygon"].is<picojson::array>()) {
				linestyle = "polygon";
				aPatrolData.TruckingMode = 1;
			}
			/*最初の点のワールド座標位置*/
			double rootX = aObject["x"].get<double>();
			double rootY = aObject["y"].get<double>();
			picojson::array pointsArray = aObject[linestyle].get<picojson::array>();
			for (int p = 0; p < pointsArray.size(); ++p)
			{
				double x = rootX + pointsArray[p].get <picojson::object>()["x"].get<double>();
				double y = rootY + pointsArray[p].get <picojson::object>()["y"].get<double>();

				aPatrolData.PatrolPoints.push_back({ x,y });
			}
			/*巡回経路に割り振られたID読み込み*/
			int id = static_cast<int>(aObject["id"].get<double>());
			aPatrolData.ID = id;
			/*mapにIDをキーとして巡回ルート登録*/
			_patrolPoints[id] = aPatrolData;
		}
	}
}

void MapChip::LoadEnemyVIPPatrolLine(picojson::array aObjects) {
	for (int i = 0; i < aObjects.size(); ++i) {
		picojson::object aObject = aObjects[i].get<picojson::object>();
		ServerMachineData data;
		/*height=0はPolylineかpolygonによる巡回ルートオブジェクト*/
		if (aObject["polygon"].is<picojson::array>() ||
			aObject["polyline"].is<picojson::array>()) {
			/*敵1体分の巡回ルート*/
			EnemyPatrol aPatrolData;
			std::string linestyle = "null";
			/*polylineが存在するか確認*/
			if (aObject["polyline"].is<picojson::array>()) {
				linestyle = "polyline";
				aPatrolData.TruckingMode = 0;
			}
			/*polygonが存在するか確認*/
			else if (aObject["polygon"].is<picojson::array>()) {
				linestyle = "polygon";
				aPatrolData.TruckingMode = 1;
			}
			/*polylineかpolygonがあれば巡回座標読み込み*/
			if (linestyle != "null")
			{
				picojson::array pointsArray = aObject[linestyle].get<picojson::array>();
				for (int p = 0; p < pointsArray.size(); ++p)
				{
					double x = pointsArray[p].get <picojson::object>()["x"].get<double>();
					double y = pointsArray[p].get <picojson::object>()["y"].get<double>();
					x += aObject["x"].get<double>();
					y += aObject["y"].get<double>() - _chipSize_H;
					Vector2 pos = { x,y };
					aPatrolData.PatrolPoints.push_back(pos);
				}
				/*巡回ルートに対応するID読み混み*/
				int id = static_cast<int>(aObject["id"].get<double>());
				aPatrolData.ID = id;
				/*mapにIDをキーとして巡回ルート登録*/
				_patrolPointsVIP.push_back(aPatrolData);
			}
		}
	}
}

EnemyPatrol MapChip::FindPatrol(int id) {
	EnemyPatrol data;
	auto points = _patrolPoints.find(id);
	if (points != _patrolPoints.end()) {
		return points->second;
	}
	return data;
}

PlayerData MapChip::GetPlayerData(int playerno) {
	PlayerData data;
	if (_playerData.find(playerno + 1) != _playerData.end()) {
		return _playerData[playerno + 1];
	}
	return data;
}
void MapChip::SetBasicObjectData(picojson::object object, std::unique_ptr<ObjectDataBase>& data) {
	data->ID = static_cast<int>(object["id"].get<double>());
	data->pos.x = object["x"].get<double>();
	data->pos.y = object["y"].get<double>() - _chipSize_H;
}

void MapChip::FindPropertieData(int& data, picojson::array properties, std::string name) {
	for (int i = 0; i < properties.size(); ++i) {
		picojson::object aPropatie = properties[i].get<picojson::object>();
		if (aPropatie["name"].get<std::string>() == name) {
			data = static_cast<int>(aPropatie["value"].get<double>());
		}
	}
}
void MapChip::FindPropertieData(double& data, picojson::array properties, std::string name) {
	for (int i = 0; i < properties.size(); ++i) {
		picojson::object aPropatie = properties[i].get<picojson::object>();
		if (aPropatie["name"].get<std::string>() == name) {
			data = aPropatie["value"].get<double>();
		}
	}
}
void MapChip::FindPropertieData(bool& data, picojson::array properties, std::string name) {
	for (int i = 0; i < properties.size(); ++i) {
		picojson::object aPropatie = properties[i].get<picojson::object>();
		if (aPropatie["name"].get<std::string>() == name) {
			data = aPropatie["value"].get<bool>();
		}
	}
}
void MapChip::FindPropertieData(std::string& data, picojson::array properties, std::string name) {
	for (int i = 0; i < properties.size(); ++i) {
		picojson::object aPropatie = properties[i].get<picojson::object>();
		if (aPropatie["name"].get<std::string>() == name) {
			data = aPropatie["value"].get<std::string>();
		}
	}
}

void MapChip::LoadEnemyClass(picojson::object object, EnemyData data) {
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.waitFrame, properties, "WaitFrame");
		FindPropertieData(data.patrolID, properties, "PatrolLine");
	}
	_enemyDataList.push_back(data);
}

void MapChip::LoadEnemyBClass(picojson::object object, EnemyBData data) {
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.Direction[0], properties, "Direction1");
		FindPropertieData(data.Direction[1], properties, "Direction2");
		FindPropertieData(data.Direction[2], properties, "Direction3");
		FindPropertieData(data.Direction[3], properties, "Direction4");
		FindPropertieData(data.LookTime[0], properties, "LookTime1");
		FindPropertieData(data.LookTime[1], properties, "LookTime2");
		FindPropertieData(data.LookTime[2], properties, "LookTime3");
		FindPropertieData(data.LookTime[3], properties, "LookTime4");
		FindPropertieData(data.detectionComplete, properties, "FindTime");
		FindPropertieData(data.sightH, properties, "Sight_H");
		FindPropertieData(data.sightW, properties, "Sight_W");
	}
	_enemyBDataList.push_back(data);
}

void MapChip::LoadDoorClass(picojson::object object, DoorData data) {
	_doorDataList.push_back(data);
}

void MapChip::LoadItemAmmoClass(picojson::object object, BulletItemData data) {
	_bulletItems.push_back(data);
}

void MapChip::LoadItemHPClass(picojson::object object, HPItemData data) {
	_hpItems.push_back(data);
}

void MapChip::LoadLightClass(picojson::object object, SquareLightStats data) {
	if (object["properties"].is<picojson::array>()) {
		auto properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.activate, properties, "Activate");
		FindPropertieData(data.alpha, properties, "Color : A");
		FindPropertieData(data.b, properties, "Color : B");
		FindPropertieData(data.g, properties, "Color : G");
		FindPropertieData(data.r, properties, "Color : R");
		FindPropertieData(data.object, properties, "ObjectImage");
		FindPropertieData(data.image, properties, "Image");
		FindPropertieData(data.size.x, properties, "Size_X");
		FindPropertieData(data.size.y, properties, "Size_Y");
	}
	data.pos = { object["x"].get<double>() - (data.size.x / 2),
	object["y"].get<double>() - (data.size.y / 2) - _chipSize_H };
	_lightDataList.push_back(data);
}

void MapChip::LoadMineClass(picojson::object object, MineData data) {
	std::string direction{ "none" };
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(direction, properties, "Direction");
		FindPropertieData(data.range, properties, "Range");
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
	_mineDataList.push_back(data);
}

void MapChip::LoadPlayerClass(picojson::object object, PlayerData data) {
	int playerno{ data.Player };
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(playerno, properties, "Player");
		FindPropertieData(data.Accelerate, properties, "Accelerate");
		FindPropertieData(data.Friction, properties, "Friction");
		FindPropertieData(data.SpeedMax, properties, "SpeedMax");
		FindPropertieData(data.SlowSpeedRate, properties, "ChargeWalkRate");
	}
	_playerData[playerno] = data;
}

void MapChip::LoadScreenPumpClass(picojson::object object, ScreenPumpData data) {
	std::string direction{ "none" };
	if (object["properties"].is<picojson::array>()) {
		auto properties = object["properties"].get<picojson::array>();
		FindPropertieData(direction, properties, "Direction");
		FindPropertieData(data.range, properties, "Range");
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
	_screenPumpDataList.push_back(data);
}

void MapChip::LoadServerClass(picojson::object object, ServerMachineData data) {
	if (object["properties"].is<picojson::array>())
	{
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.upperleft, properties, "upperleft");
		FindPropertieData(data.Direction, properties, "Direction");
	}
	if (data.upperleft == true) {
		_serverMachineDataList.push_back(data);
	}
}

void MapChip::LoadStickyBombClass(picojson::object object, StickyBombData data) {
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.range, properties, "Range");
		FindPropertieData(data.timer, properties, "Timer");
	}
	_stickyBombDataList.push_back(data);
}

void MapChip::LoadSwitchClass(picojson::object object, SwitchData data) {
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.RedFlag, properties, "RedFlag");
		FindPropertieData(data.projectionNumber, properties, "EffectNumber");
		for (int i = 0; i < properties.size(); ++i) {
			if (properties[i].get<picojson::object>()["name"].get<std::string>().find("LinkGimmick") != std::string::npos) {
				data.links.push_back(static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>()));
			}

		}
	}
	_switchDataList.push_back(data);
}

void MapChip::LoadSwitchAreaClass(picojson::object object, SwitchAreaData data) {
	if (object["properties"].is<picojson::array>()) {
		auto properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.Reverse, properties, "Reverse");
		for (int i = 0; i < properties.size(); ++i) {
			if (properties[i].get<picojson::object>()["name"].get<std::string>().find("LinkGimmick") != std::string::npos) {
				data.links.push_back(static_cast<int>(properties[i].get<picojson::object>()["value"].get<double>()));
			}
		}

	}
	_switchAreaDataList.push_back(data);
}

void MapChip::LoadTeleport_INClass(picojson::object object, teleporterData data) {
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.random, properties, "Random");
		FindPropertieData(data.tereortID, properties, "Teleport_OUT");
	}
	if (data.random == true || data.tereortID != -1) {
		_teleporterInDataList.push_back(data);
	}
}

void MapChip::LoadTeleport_OUTClass(picojson::object object, TeleporterOutData data) {
	if (object["properties"].is<picojson::array>()) {
		auto properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.random, properties, "RandomPort");
	}
	_teleporterOutDataList.push_back(data);
}

void MapChip::LoadTNTClass(picojson::object object, TNTData data) {
	_tNTDataList.push_back(data);
}
void MapChip::LoadDigitalLetterClass(picojson::object object, DigitalLetterData data) {
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		for (int i = 0; i < properties.size(); ++i) {
			if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Message") {
				std::string ss = properties[i].get<picojson::object>()["value"].get<std::string>();
				std::wstring w_ss = utf8_to_wide(ss);
				data.message = wide_to_sjis(w_ss);
			}
			if (properties[i].get<picojson::object>()["name"].get<std::string>() == "Image") {
				std::string ss = properties[i].get<picojson::object>()["value"].get<std::string>();
				data.image = ImageServer::LoadGraph(ss);
			}
		}
	}
	_deditalLetterData.push_back(data);
}

void MapChip::LoadBarrierClass(picojson::object object, BarrierData data) {
	_barrierDataList.push_back(data);
}
void MapChip::LoadBossGeneratorClass(picojson::object object, BigGeneratorData data) {
	_bigGeneratorDataList.push_back(data);
}
void MapChip::LoadBossRailGunClass(picojson::object object, BigGunData data) {
	_bigGunDataList.push_back(data);
}
void MapChip::LoadBossServerClass(picojson::object object, BigServerData data) {
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.Direction, properties, "Direction");
	}
	_bigServerDataList.push_back(data);
}
void MapChip::LoadBossTriggerClass(picojson::object object, BossGimmickControllerData data) {
	if (object["properties"].is<picojson::array>()) {
		picojson::array properties = object["properties"].get<picojson::array>();
		FindPropertieData(data.teleporterID, properties, "Teleporter");
	}
	_bossGimmickControllerDataList.push_back(data);
}
void MapChip::LoadBreakableObjectClass(picojson::object object, BreakableObjectData data) {
	_breakableObjectData.push_back(data);
}

void MapChip::Render(Vector2 windowPos, Vector2 cameraPos, std::string layer) {
	std::vector<std::vector<std::vector<int>>> tiledata;
	if (layer == "middle") {
		tiledata = _mapTileData;
	}
	else if (layer == "front") {
		tiledata = _mapFrontTileData;
	}
	else {
		tiledata = _mapBackTileData;
	}

	int x, y;
	for (int layer = 0; layer < tiledata.size(); ++layer)
	{
		for (y = cameraPos.y / _chipSize_H; y < (cameraPos.y + screen_H) / _chipSize_H; ++y)
		{
			for (x = cameraPos.x / _chipSize_W; x < (cameraPos.x + splitscreen_W) / _chipSize_W; ++x)
			{
				int layerstart = _mapSize_W * _mapSize_H * layer;
				int index = y * _mapSize_W + x;
				int pos_x = x * _chipSize_W + static_cast<int>(windowPos.x) - static_cast<int>(cameraPos.x);
				int pos_y = y * _chipSize_H + static_cast<int>(windowPos.y) - static_cast<int>(cameraPos.y);
				int chip_no = tiledata[layer][y][x];
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

void MapChip::MiniMapRender(int stageNum, Vector2 windowPos, Vector2 cameraPos, bool bossflag)
{
	float scalex{ 1 }, scaley{ 1 };;
	if (bossflag) {
		scalex = static_cast<float>(345.0 * 4.0 / (_mapSize_W * _chipSize_W));
		scaley = static_cast<float>(400.0 * 4.0 / (_mapSize_H * _chipSize_H));
	}
	else {
		scalex = static_cast<float>(345.0 / (_mapSize_W * _chipSize_W));
		scaley = static_cast<float>(400.0 / (_mapSize_H * _chipSize_H));
	}

	for (int i = 0; i < _minimapData.size(); ++i)
	{
		int plotsize = static_cast<int>(_minimapData[i].second.size());
		unsigned int color = _minimapData[i].first;
		for (int plot = 0; plot < plotsize; ++plot)
		{

			DrawLineAA(static_cast<float>(_minimapData[i].second[plot].x * scalex + windowPos.x),
				static_cast<float>(_minimapData[i].second[plot].y * scaley + windowPos.y),
				static_cast<float>(_minimapData[i].second[(plot + 1) % plotsize].x * scalex + windowPos.x),
				static_cast<float>(_minimapData[i].second[(plot + 1) % plotsize].y * scaley + windowPos.y),
				color);
		}
	}
}

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
//  backlayer trueなら後ろのレイヤーとの接触も見る
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
std::vector<int> MapChip::CheckHitChipNo(int x, int y, bool backlayer)
{
	std::vector<int> v_chip_no;
	v_chip_no.resize(0);
	// マップチップ位置はマップデータからはみ出ているか？
	if (0 <= x && x < _mapSize_W && 0 <= y && y < _mapSize_H)
	{
		// マップチップIDが0以外は当たり判定を行う
		for (int layer = 0; layer < _mapTileData.size(); ++layer) {
			int chip_no = _mapTileData[layer][y][x];
			v_chip_no.emplace_back(chip_no);
		}
		if (backlayer) {
			// マップチップIDが0以外は当たり判定を行う
			for (int layer = 0; layer < _mapBackTileData.size(); ++layer) {
				int chip_no = _mapBackTileData[layer][y][x];
				v_chip_no.emplace_back(chip_no);
			}
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
bool MapChip::IsHit(AABB col, bool backlayer)
{
	// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
	for (int y = static_cast<int>(col.min.y) / _chipSize_H; y <= static_cast<int>(col.max.y) / _chipSize_H; y++)
	{
		for (int x = static_cast<int>(col.min.x) / _chipSize_W; x <= static_cast<int>(col.max.x) / _chipSize_W; x++)
		{
			std::vector<int> v_chip_no = CheckHitChipNo(x, y, backlayer);
			/*触れているチップのgidでループ*/
			for (int chip_gid : v_chip_no) {
				/*コリジョンを持つチップのgidでループ*/
				for (int col_gid : _chipCollision) {
					/*触れているチップの中にコリジョンを持つチップが有ればtrueを返す*/
					if (chip_gid == col_gid) {
						return true;
					}
				}
			}
		}
	}
	// 当たらなかった
	return false;
}

/*視線判定用*/
bool MapChip::IsHit(std::set<std::pair<int, int>> grids) {
	for (auto&& grid : grids) {
		std::vector<int> v_chip_no = CheckHitChipNo(grid.first, grid.second, false);
		for (int chip_gid : v_chip_no) {
			/*コリジョンを持つチップのgidでループ*/
			for (int col_gid : _chipCollision) {
				/*触れているチップの中にコリジョンを持つチップが有ればtrueを返す*/
				if (chip_gid == col_gid) {
					return true;
				}
			}
			for (int col_gid : _gidBarrier1) {
				/*触れているチップの中にコリジョンを持つチップが有ればtrueを返す*/
				if (chip_gid == col_gid) {
					return true;
				}
			}
			for (int col_gid : _gidBarrier2) {
				/*触れているチップの中にコリジョンを持つチップが有ればtrueを返す*/
				if (chip_gid == col_gid) {
					return true;
				}
			}
		}
	}
	return false;
}

// オブジェクトとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//  
//   o = オブジェクト
// 戻値：
//   0 : 当たってない
//   1 : 当たった
bool MapChip::IsHitBarrier(AABB col, int playerno)
{
	/*
	// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
	for (int y = static_cast<int>(col.min.y) / _chipSize_H; y <= static_cast<int>(col.max.y) / _chipSize_H; y++)
	{
		for (int x = static_cast<int>(col.min.x) / _chipSize_W; x <= static_cast<int>(col.max.x) / _chipSize_W; x++)
		{
			// (x,y)は、マップチップの座標（チップ単位）
			// この位置のチップは当たるか？
			std::vector<int> v_chip_no = CheckHitChipNo(x, y, true);
			for (int chip_no : v_chip_no) {
				if (playerno == 0) {
					for (auto gid : _gidBarrier1) {
						if (chip_no == gid)
						{	// このチップと当たった。
							// 当たったので戻る
							return 1;
						}
					}
					for (auto gid : _gidBarrier2) {
						if (chip_no == gid)
						{	// このチップと当たった。
							// 当たったので戻る
							if (CheckSoundMem(SoundServer::Find("EnterBarrier")) == 0) {
								PlaySoundMem(SoundServer::Find("EnterBarrier"), DX_PLAYTYPE_BACK);
							}
							continue;
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
					for (auto gid : _gidBarrier1) {
						if (chip_no == gid)
						{	// このチップと当たった。
							// 当たったので戻る
							if (CheckSoundMem(SoundServer::Find("EnterBarrier")) == 0) {
								PlaySoundMem(SoundServer::Find("EnterBarrier"), DX_PLAYTYPE_BACK);
							}
							continue;
						}
					}
				}
			}
		}
	}
	*/
	// 当たらなかった
	return 0;
}