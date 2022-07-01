#include <DxLib.h>
#include"MapChip.h"
#include "picojson/picojson.h"
#include "Camera.h"
#include "ImageServer.h"

#include <memory>
#include <fstream>


MapChips::MapChips(Game& game) :_game{game}{
	_mapData.clear();
	LoadMap("resource/", "test_01.json");
	LoadMap("resource/", "test_02.json");
	LoadMap("resource/", "test_03.json");

}

MapChips::~MapChips() {
	_mapData.clear();
}

bool MapChips::LoadMap(std::string folderpath, std::string filename) {

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
	for (int i = 0; i < aLayers.size(); i++) {

		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// ���C���[�I�u�W�F�N�g
		// ���C���[��ނ��utilelayer�v�̂��̂��J�E���g����
		if (jsLayer["type"].get<std::string>() == "tilelayer") {
			picojson::array aData = jsLayer["data"].get<picojson::array>();			// �}�b�v�z��
			int index = 0;
			std::vector<std::vector<MapChip>>	vMapLayer;	// 1���C���[���̃f�[�^
			for (int y = 0; y < _mapSize_H; y++) {
				std::vector<MapChip>	vMapLine;	// 1�s���̃f�[�^
				for (int x = 0; x < _mapSize_W; x++) {
					MapChip chip;
					chip._id = (int)aData[index].get<double>();
					vMapLine.push_back(chip);
					index++;
				}
				vMapLayer.push_back(vMapLine);
			}
			// ���C���[�f�[�^��ǉ�
			std::vector<std::vector<std::vector<MapChip>>>onestagedata;
			onestagedata.push_back(vMapLayer);
			_mapData.push_back(onestagedata);
		}
	}

	return true;
}

void MapChips::Render(int stageNum,Vector2 windowPos,Vector2 cameraPos) {

	int x, y;
	for (int layer = 0; layer < _mapData[stageNum].size(); ++layer)
	{
		for (y = 0; y < _mapSize_H; ++y)
		{
			for(x = 0 ; x < _mapSize_W ; ++x)
			{
				int layerstart = _mapSize_W * _mapSize_H * layer;
				int index = y * _mapSize_W + x;
				int pos_x = x * _chipSize_W +static_cast<int>(windowPos.x) - static_cast<int>(cameraPos.x);
				int pos_y = y * _chipSize_H + static_cast<int>(windowPos.y) - static_cast<int>(cameraPos.y);
				int chip_no = _mapData[stageNum][layer][y][x]._id;

				chip_no--;

				if (chip_no >= 0) {
					DrawGraph(pos_x, pos_y, _cgChip[chip_no], TRUE);
				}
				
			}
		}
	}
}

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
int MapChips::CheckHit(int stagenum,int x, int y)
{
	// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
	if (0 <= x && x < _mapSize_W && 0 <= y && y < _mapSize_H)
	{	// �݂͂łĂ��Ȃ�

		// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
		// ���݁A���C���[�͍l������Ă��Ȃ�
		int layer = 0;
		int chip_no = _mapData[stagenum][layer][y][x]._id;

			if (chip_no == 2)
			{
				// ��������
				return chip_no;
			}
			
		
	}
	
	// �������Ă��Ȃ�
	return 0;
}



// �I�u�W�F�N�g�ƃ}�b�v�`�b�v�������������̔���A����ѓ��������ꍇ�̏���
// �����F
//   o = �I�u�W�F�N�g
//   mxormy�@�ړ���
//   xory �ړ������@0�Ȃ�x,1�Ȃ�y
// �ߒl�F
//   0 : �������ĂȂ�
//   1 : ��������
int MapChips::IsHit(int objectstage,Actor& o, int mxormy)
{
	int x, y;
	int dxordy=0;

	// �L������`���쐬����
	int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
	l = o.GetPosition().x ;
	t = o.GetPosition().y;
	r = o.GetPosition().x+o.GetSize().x;
	b = o.GetPosition().y + o.GetSize().y;

	// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
	for (y = t / _chipSize_H; y <= b / _chipSize_H; y++)
	{
		for (x = l / _chipSize_W; x <= r / _chipSize_W; x++)
		{
			// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
			// ���̈ʒu�̃`�b�v�͓����邩�H
			int chip_no = CheckHit(objectstage,x, y);
			if (chip_no != 0)
			{	// ���̃`�b�v�Ɠ��������B
				// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
				if (mxormy < 0)
				{	// ���ɓ����Ă����̂ŁA�E�ɕ␳
					dxordy = 1;
				}

				if (mxormy > 0)
				{	// �E�ɓ����Ă����̂ŁA���ɕ␳
					dxordy = -1;
				}

				// ���������̂Ŗ߂�
				return dxordy;
			}
		}
	}

	// ������Ȃ�����

	return 0;
}

