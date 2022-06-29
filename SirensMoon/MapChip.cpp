#include <DxLib.h>
#include"MapChip.h"
#include "picojson/picojson.h"
#include "Camera.h"
#pragma warning(disable : 4996)

MapChip::MapChip(Game& game) :
	_game{game}
{
	LoadMap("resource/test_01.json");

	_cgChip = new int[_chipCount];
	LoadDivGraph("resource/platformer_simpleA_sheet.png",
		_chipCount, _chipCount_W, _chipCount_H, _chipSize_W, _chipSize_H, _cgChip);
}

MapChip::~MapChip() {
	delete[] _cgChip;
	delete[] _nMap;
}

int MapChip::LoadMap(const char* jsonfile) {
	// ファイルを開いてstringを取得する
	FILE* fp;
	fp = fopen(jsonfile, "rb");
	// ファイルのサイズを取得
	fseek(fp, 0, SEEK_END); int size = ftell(fp); fseek(fp, 0, SEEK_SET);

	char* p = new char[size + 1];

	fread(p, 1, size, fp);

	fclose(fp);
	p[size] = '\0';

	picojson::value json;
	picojson::parse(json, p);
	picojson::object jsRoot = json.get<picojson::object>();

	_mapSize_W = static_cast<int>(jsRoot["width"].get<double>());
	_mapSize_H = static_cast<int>(jsRoot["height"].get<double>());

	// タイルセット取得(1つのみ対応)
	picojson::array aTileSets = jsRoot["tilesets"].get<picojson::array>();
	picojson::object jsTile = aTileSets[0].get<picojson::object>();
	_chipCount = (int)jsTile["tilecount"].get<double>();
	_chipCount_W = (int)jsTile["columns"].get<double>();
	_chipCount_H = (_chipCount / _chipCount_W);		// 計算で出す
	_chipSize_W = (int)jsRoot["tilewidth"].get<double>();
	_chipSize_H = (int)jsRoot["tileheight"].get<double>();
	std::string strChipFile = jsTile["image"].get<std::string>();

	// レイヤー情報の取得
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();
	// マップの"tilelayer"レイヤー数を数える
	int layer;
	layer = 0;
	for (int i = 0; i < aLayers.size(); ++i)
	{
		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// レイヤーオブジェクト
		// レイヤー種類が「tilelayer」のものをカウントする
		if (jsLayer["type"].get<std::string>() == "tilelayer")
		{
			layer++;
		}
	}
	_mapSize_Layer = layer;

	// レイヤー内データの取得
	_nMap = new int[(int)(_mapSize_Layer * _mapSize_W * _mapSize_H)];
	layer = 0;
	for (int i = 0; i < aLayers.size(); ++i)
	{
		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// レイヤーオブジェクト
		// レイヤー種類が「tilelayer」のものをカウントする
		if (jsLayer["type"].get<std::string>() == "tilelayer")
		{
			picojson::array aData = jsLayer["data"].get<picojson::array>();			// マップ配列
			for (int y = 0; y < _mapSize_H; ++y)
			{
				for (int x = 0; x < _mapSize_W; ++x)
				{
					int layerstart = _mapSize_W * _mapSize_H * layer;
					int index = y * _mapSize_W + x;
					_nMap[layerstart + index] = (int)aData[index].get<double>();
				}
			}
			layer++;
		}
	}

	// メモリ破棄
	delete[] p;

	return 1;
}

void MapChip::Render(Vector2 windowPos,Vector2 cameraPos) {

	int x, y;
	
	for (int layer = 0; layer < _mapSize_Layer; ++layer)
	{
		for (y = 0; y < _mapSize_H; ++y)
		{
			for(x = 0 ; x < _mapSize_W ; ++x)
			{
				int layerstart = _mapSize_W * _mapSize_H * layer;
				int index = y * _mapSize_W + x;
				int pos_x = x * _chipSize_W +static_cast<int>(windowPos.x) - static_cast<int>(cameraPos.x);
				int pos_y = y * _chipSize_H + static_cast<int>(windowPos.y) - static_cast<int>(cameraPos.y);
				int chip_no = _nMap[layerstart + index];

				chip_no--;

				if (chip_no >= 0) {
					DrawGraph(pos_x, pos_y, _cgChip[chip_no], TRUE);
				}
				
			}
		}
	}
}





