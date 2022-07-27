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
	LoadMap("resource/", "TestMap_01.json");
}

MapChips::~MapChips() {
	_mapDataStandard.clear();
	_mapDataRecon.clear();
}

bool MapChips::LoadMap(std::string folderpath, std::string filename) 
{

	// �t�@�C������json�f�[�^�̓ǂݍ���
	std::ifstream ifs(folderpath + filename);
	picojson::value json;
	ifs >> json;

	// json�f�[�^����p�����[�^���擾
	picojson::object jsRoot = json.get<picojson::object>();
	_mapSize_W = (int)jsRoot["width"].get<double>();
	_mapSize_H = (int)jsRoot["height"].get<double>();

	// �^�C���Z�b�g�擾(1�̂ݑΉ�)
	picojson::array aTileSets = jsRoot["tilesets"].get<picojson::array>();
	picojson::object jsTile = aTileSets[0].get<picojson::object>();
	_chipCount = (int)jsTile["tilecount"].get<double>();
	_chipCount_W = (int)jsTile["columns"].get<double>();
	_chipCount_H = (_chipCount / _chipCount_W);		// �v�Z�ŏo��
	_chipSize_W = (int)jsRoot["tilewidth"].get<double>();
	_chipSize_H = (int)jsRoot["tileheight"].get<double>();
	std::string strChipFile = jsTile["image"].get<std::string>();       // �摜�t�@�C����

	// �`�b�v�摜�ǂݍ���
	_cgChip.resize(_chipCount);
	ImageServer::LoadDivGraph((folderpath + strChipFile).c_str()
		, _chipCount, _chipCount_W, _chipCount_H
		, _chipSize_W, _chipSize_H
		, _cgChip.data());


	// ���C���[���̎擾
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();

	// ���C���[���f�[�^�̎擾
	std::vector<std::vector<std::vector<int>>>onestagedata;
	/*��̃X�e�[�W�̃|���S���f�[�^*/
	std::vector<std::vector<Vector2>>  onestagepolygons;
	/*1�X�e�[�W���̃G�l�~�[�f�[�^*/
	std::vector<EnemyData> aEnemyData;
	for (int i = 0; i < aLayers.size(); i++) 
	{

		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// ���C���[�I�u�W�F�N�g

		// ���C���[��ނ��utilelayer�v�̂���
		if (jsLayer["type"].get<std::string>() == "tilelayer") 
		{
			picojson::array aData = jsLayer["data"].get<picojson::array>();			// �}�b�v�z��
			int index = 0;
			std::vector<std::vector<int>>	vMapLayer;	// 1���C���[���̃f�[�^
			for (int y = 0; y < _mapSize_H; y++) {
				std::vector<int>	vMapLine;	// 1�s���̃f�[�^
				for (int x = 0; x < _mapSize_W; x++) {
					int chip_id;
					chip_id = (int)aData[index].get<double>();
					vMapLine.push_back(chip_id);
					index++;
				}
				vMapLayer.push_back(vMapLine);
			}
			// ���C���[�f�[�^��ǉ�
			onestagedata.push_back(vMapLayer);
		}
		/*���C���[�̖��O��MiniMap�̕����擾*/
		else if (jsLayer["name"].get<std::string>() == "MiniMap") 
		{
			/*�I�u�W�F�N�g�i�|���S���j�̐����m�F�A�񐔕����[�v*/
			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			for (int i = 0; i < aObjects.size(); ++i)
			{
				/*��̃|���S���̒��_�f�[�^*/
				std::vector<Vector2> polygonplots;
				/*�|���S���̒��_�������[�v*/
				picojson::array polylineplots = aObjects[i].get<picojson::object>()["polyline"].get<picojson::array>();
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
				if (aObjects[i].get<picojson::object>()["gid"].get<double>() == 8) {
					posX = aObjects[i].get<picojson::object>()["x"].get<double>();
					posY = aObjects[i].get<picojson::object>()["y"].get<double>();
					Vector2 pos = { posX,posY };
					aBulletPosition.push_back(pos);
				}
				else if (aObjects[i].get<picojson::object>()["gid"].get<double>() == 9) {
					posX = aObjects[i].get<picojson::object>()["x"].get<double>();
					posY = aObjects[i].get<picojson::object>()["y"].get<double>();
					Vector2 pos = { posX,posY };
					aHPPosition.push_back(pos);
				}
			}
			_hpItems.push_back(aHPPosition);
			_bulletItems.push_back(aBulletPosition);
		}
		else if (jsLayer["name"].get<std::string>() == "Enemy") 
		{
			picojson::array aObjects = jsLayer["objects"].get<picojson::array>();
			for (int i = 0; i < aObjects.size(); ++i) {
				/*�}�b�v�^�C��3�Ԃ̓G�l�~�[*/
				if (aObjects[i].get<picojson::object>()["gid"].get<double>()==3){

					int aEnemyID;
					int     aEnemyType;
					Vector2	aEnemyPosition;
					int aPatrolID;

					aEnemyID = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());

					picojson::array properties = aObjects[i].get<picojson::object>()["properties"].get<picojson::array>();

					aEnemyType =static_cast<int>(properties[0].get<picojson::object>()["value"].get<double>());
					aPatrolID = static_cast<int>(properties[1].get<picojson::object>()["value"].get<double>());

					double posX = aObjects[i].get<picojson::object>()["x"].get<double>();
					double posY = aObjects[i].get<picojson::object>()["y"].get<double>();
					aEnemyPosition = { posX,posY };
					aEnemyData.push_back({ aEnemyID,aEnemyType, aEnemyPosition, aPatrolID });
				}
				/*height=0��Polyline��polygon�ɂ�鏄�񃋁[�g�I�u�W�F�N�g*/
				else if(aObjects[i].get<picojson::object>()["polygon"].is<double>()||
					aObjects[i].get<picojson::object>()["polyline"].is<double>()) {
					/*�G1�̕��̏��񃋁[�g*/
					EnemyPatrol aPatrolData;
					std::string linestyle = "null";
					/*polyline�����݂��邩�m�F*/
					if (aObjects[i].get<picojson::object>()["polyline"].is<picojson::array>()) {
						linestyle = "polyline";
						aPatrolData.TruckingMode = 0;
					}
					/*polygon�����݂��邩�m�F*/
					else if (aObjects[i].get<picojson::object>()["polygon"].is<picojson::array>()) {
						linestyle = "polygon";
						aPatrolData.TruckingMode = 1;
					}
					/*polyline��polygon������Ώ�����W�ǂݍ���*/
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
						/*���񃋁[�g�ɑΉ�����ID�ǂݍ���*/
						int id = static_cast<int>(aObjects[i].get<picojson::object>()["id"].get<double>());
						std::unordered_map<int, std::vector<Vector2>> map;
						/*map��ID���L�[�Ƃ��ď��񃋁[�g�o�^*/

						_patrolPoints[id] = aPatrolData;
					}
				}
				/*�c��̓T�[�o�[�̃f�[�^*/
				else {

				}

			}
			_enemyDataList.push_back(aEnemyData);
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
		int plotsize = static_cast<int>(_mapDataRecon[stageNum][i].size());
		for (int plot = 0; plot < plotsize; ++plot) 
		{
			float scale =static_cast<float>( 410.0/3240.0*0.97);
			DrawLineAA(static_cast<float>(_mapDataRecon[stageNum][i][plot].x*scale + windowPos.x),
				static_cast<float>(_mapDataRecon[stageNum][i][plot].y*scale + windowPos.y ),
				static_cast<float>(_mapDataRecon[stageNum][i][(plot + 1) % plotsize].x *scale+ windowPos.x),
				static_cast<float>(_mapDataRecon[stageNum][i][(plot + 1) % plotsize].y *scale+ windowPos.y ),
				GetColor(0, 255, 255));
		}
	}
}

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
std::vector<int> MapChips::CheckHitChipNo(int stagenum,int x, int y)
{
	std::vector<int> v_chip_no;
	// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
	if (0 <= x && x < _mapSize_W && 0 <= y && y < _mapSize_H)
	{	
		// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
		for( int layer = 0; layer < _mapDataStandard[stagenum].size(); ++layer) {
			int chip_no = _mapDataStandard[stagenum][layer][y][x];
			// ��������
			v_chip_no.emplace_back(chip_no);
		}
	}
	// �����}�b�v�`�b�v�Ɠ������Ă��Ȃ����-1������
	if (v_chip_no.size() == 0) {
		v_chip_no.emplace_back(-1);
	}
	return v_chip_no;
}


// �I�u�W�F�N�g�ƃ}�b�v�`�b�v�������������̔���A����ѓ��������ꍇ�̏���
// �����F
//  
//   o = �I�u�W�F�N�g
// �ߒl�F
//   0 : �������ĂȂ�
//   1 : ��������
bool MapChips::IsHit(int objectstage,Actor& o)
{
	int x, y;
	int dxordy=0;
	// �L������`���쐬����
	int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
	l = static_cast<int>(o.GetPosition().x);
	t = static_cast<int>(o.GetPosition().y);
	r = static_cast<int>(o.GetPosition().x+o.GetSize().x);
	b = static_cast<int>(o.GetPosition().y+o.GetSize().y);
	// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
	for (y = t / _chipSize_H; y <= b / _chipSize_H; y++)
	{
		for (x = l / _chipSize_W; x <= r / _chipSize_W; x++)
		{
			// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
			// ���̈ʒu�̃`�b�v�͓����邩�H
			std::vector<int> v_chip_no = CheckHitChipNo(objectstage,x,y);
			int list[] = {2,-1};
			for (int chip_no : v_chip_no) {
			int i = 0;
				while (list[i] != -1) {
					if (chip_no == list[i])
					{	// ���̃`�b�v�Ɠ��������B
						// ���������̂Ŗ߂�
						return 1;
					}
					++i;
				}
			}
		}
	}
	// ������Ȃ�����
	return 0;
}

// �I�u�W�F�N�g�ƃ}�b�v�`�b�v�������������̔���A����ѓ��������ꍇ�̏���
// �����F
//  
//   o = �I�u�W�F�N�g
// �ߒl�F
//   0 : �������ĂȂ�
//   1 : ��������
bool MapChips::IsHitBarrier(int objectstage, Actor& o,int playerno)
{
	int x, y;
	int dxordy = 0;

	// �L������`���쐬����
	int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
	l = static_cast<int>(o.GetPosition().x);
	t = static_cast<int>(o.GetPosition().y);
	r = static_cast<int>(o.GetPosition().x + o.GetSize().x);
	b = static_cast<int>(o.GetPosition().y + o.GetSize().y);

	// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
	for (y = t / _chipSize_H; y <= b / _chipSize_H; y++)
	{
		for (x = l / _chipSize_W; x <= r / _chipSize_W; x++)
		{
			// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
			// ���̈ʒu�̃`�b�v�͓����邩�H
			std::vector<int> v_chip_no = CheckHitChipNo(objectstage, x, y);
			for (int chip_no : v_chip_no) {
				if (playerno == 0) {
					if (chip_no == 10)
					{	// ���̃`�b�v�Ɠ��������B
						// ���������̂Ŗ߂�
						return 1;
					}
				}
				if (playerno == 1) {
					if (chip_no == 11)
					{	// ���̃`�b�v�Ɠ��������B
						// ���������̂Ŗ߂�
						return 1;
					}
				}
			}
		}
	}
	// ������Ȃ�����
	return 0;
}

MapChips::EnemyPatrol MapChips::FindPatrol(int id){
	auto points = _patrolPoints.find(id);
	if (points != _patrolPoints.end()) {
		return points->second;
	}

	return { { {0,0} }, false };
}
