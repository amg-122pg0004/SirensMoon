#include <DxLib.h>
#include"MapChip.h"
#include "picojson/picojson.h"
#include "Camera.h"
#include "ImageServer.h"

#include <memory>
#include <fstream>

MapChips::MapChips(Game& game) :_game{game}{
	_mapDataStandard.clear();
	_mapDataRecon.clear();
	LoadMap("resource/", "test3_01.json");
}

MapChips::~MapChips() {
	_mapDataStandard.clear();
	_mapDataRecon.clear();
}

bool MapChips::LoadMap(std::string folderpath, std::string filename) {

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
	picojson::object jsTile = aTileSets[0].get<picojson::object>();
	_chipCount = (int)jsTile["tilecount"].get<double>();
	_chipCount_W = (int)jsTile["columns"].get<double>();
	_chipCount_H = (_chipCount / _chipCount_W);		// 計算で出す
	_chipSize_W = (int)jsRoot["tilewidth"].get<double>();
	_chipSize_H = (int)jsRoot["tileheight"].get<double>();
	std::string strChipFile = jsTile["image"].get<std::string>();       // 画像ファイル名

	// チップ画像読み込み
	_cgChip.resize(_chipCount);
	ImageServer::LoadDivGraph((folderpath + strChipFile).c_str()
		, _chipCount, _chipCount_W, _chipCount_H
		, _chipSize_W, _chipSize_H
		, _cgChip.data());


	// レイヤー情報の取得
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();

	// レイヤー内データの取得
	std::vector<std::vector<std::vector<MapChip>>>onestagedata;
	/*一つのステージのポリゴンデータ*/
	std::vector<std::vector<Vector2>>  onestagepolygons;
	for (int i = 0; i < aLayers.size(); i++) {

		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// レイヤーオブジェクト
		// レイヤー種類が「tilelayer」のものをカウントする

		if (jsLayer["type"].get<std::string>() == "tilelayer") {
			picojson::array aData = jsLayer["data"].get<picojson::array>();			// マップ配列
			int index = 0;
			std::vector<std::vector<MapChip>>	vMapLayer;	// 1レイヤー分のデータ
			for (int y = 0; y < _mapSize_H; y++) {
				std::vector<MapChip>	vMapLine;	// 1行分のデータ
				for (int x = 0; x < _mapSize_W; x++) {
					MapChip chip;
					chip._id = (int)aData[index].get<double>();
					vMapLine.push_back(chip);
					index++;
				}
				vMapLayer.push_back(vMapLine);
			}
			// レイヤーデータを追加

			onestagedata.push_back(vMapLayer);

		}
		/*レイヤーの種類がオブジェクトグループの物をカウント*/
		else if (jsLayer["type"].get<std::string>() == "objectgroup") {
			/*オブジェクト（ポリゴン）の数を確認、回数分ループ*/
			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			for (int i = 0; i < aObjects.size(); ++i) 
			{
				/*一つのポリゴンの頂点データ*/
			std::vector<Vector2> polygonplots;
				/*ポリゴンの頂点数分ループ*/
				picojson::array polylineplots = aObjects[i].get<picojson::object>()["polygon"].get<picojson::array>();
				for (int i2 = 0; i2 < polylineplots.size(); ++i2) 
				{
					auto x = polylineplots[i2].get<picojson::object>()["x"].get<double>()
						+ aObjects[i].get<picojson::object>()["x"].get<double>();
					auto y = polylineplots[i2].get<picojson::object>()["y"].get<double>()
						+ aObjects[i].get<picojson::object>()["y"].get<double>();;
					Vector2 plot = { x,y };
					polygonplots.push_back(plot);
				}
			onestagepolygons.push_back(polygonplots);
			}
		}
	}
	_mapDataStandard.push_back(onestagedata);
	_mapDataRecon.push_back(onestagepolygons);

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
				int chip_no = _mapDataStandard[stageNum][layer][y][x]._id;

				chip_no--;

				if (chip_no >= 0) {
					DrawGraph(pos_x, pos_y, _cgChip[chip_no], TRUE);
				}
			}
		}
	}
}

void MapChips::ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos) 
{
	for (int i = 0; i < _mapDataRecon[stageNum].size(); ++i) 
	{
		int plotsize = _mapDataRecon[stageNum][i].size();
		for (int plot = 0; plot < plotsize; ++plot) 
		{
			DrawLineAA(_mapDataRecon[stageNum][i][plot].x + static_cast<int>(windowPos.x),
				_mapDataRecon[stageNum][i][plot].y + static_cast<int>(windowPos.y),
				_mapDataRecon[stageNum][i][(plot + 1)%plotsize].x + static_cast<int>(windowPos.x),
				_mapDataRecon[stageNum][i][(plot + 1)%plotsize].y + static_cast<int>(windowPos.y),
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
int MapChips::CheckHitChipNo(int stagenum,int x, int y)
{
	// マップチップ位置はマップデータからはみ出ているか？
	if (0 <= x && x < _mapSize_W && 0 <= y && y < _mapSize_H)
	{	// はみでていない
		
		//int layer = 0;
		//int chip_no = _mapData[stagenum][layer][y][x]._id;

		// 当たった
		//return chip_no;
		
		// マップチップIDが0以外は当たり判定を行う
		// 現在、レイヤーは考慮されていない
		for( int layer = 0; layer <= 1; ++layer ) {
			int chip_no = _mapDataStandard[stagenum][layer][y][x]._id;
			// 当たった
			return chip_no;
		}
	}
	// 当たっていない
	return 0;
}



// オブジェクトとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//   o = オブジェクト
//   mxormy　移動量
//   xory 移動方向　0ならx,1ならy
// 戻値：
//   0 : 当たってない
//   1 : 当たった
int MapChips::IsHit(int objectstage,Actor& o, int mxormy)
{
	int x, y;
	int dxordy=0;

	// キャラ矩形を作成する
	int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
	l = static_cast<int>(o.GetPosition().x);
	t = static_cast<int>(o.GetPosition().y);
	r = static_cast<int>(o.GetPosition().x+o.GetSize().x);
	b = static_cast<int>(o.GetPosition().y + o.GetSize().y);

	// キャラの左上座標〜右下座標にあたるマップチップと、当たり判定を行う
	for (y = t / _chipSize_H; y <= b / _chipSize_H; y++)
	{
		for (x = l / _chipSize_W; x <= r / _chipSize_W; x++)
		{
			// (x,y)は、マップチップの座標（チップ単位）
			// この位置のチップは当たるか？
			int chip_no = CheckHitChipNo(objectstage,x,y);
			if (chip_no == 2)
			{	// このチップと当たった。
				// X,Yの移動方向を見て、その反対方向に補正する
				if (mxormy < 0)
				{	// 左に動いていたので、右に補正
					dxordy = 1;
				}
				if (mxormy > 0)
				{	// 右に動いていたので、左に補正
					dxordy = -1;
				}
				// 当たったので戻る
				return dxordy;
			}
		}
	}
	// 当たらなかった
	return 0;
}
/*
int MapChips::CheckTransitionChip(int renderstage, Actor& o) {
	int x, y;
	x = (static_cast<int>(o.GetPosition().x) + static_cast<int>(o.GetSize().x / 2)) / _chipSize_W;
	y = (static_cast<int>(o.GetPosition().y) + static_cast<int>(o.GetSize().y / 2))/_chipSize_H;

	// (x,y)は、マップチップの座標（チップ単位）
	// この位置のチップは当たるか？
	int chip_no = _mapData[renderstage-1][1][y][x]._id;

	switch (chip_no) {
	case 23:
		return 1;
	case 24:
		return 2;
	case 25:
		return 3;
	case 26:
		return 4;
	case 27:
		return -1;
	case 28:
		return -2;
	case 29:
		return -3;
	case 30:
		return -4;
	default:
		return 0;
	}
}

*/