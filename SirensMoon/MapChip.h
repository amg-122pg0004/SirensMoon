#pragma once
#include <unordered_map>
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>
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
	 * \brief �^�C���̕\�����s���֐�
	 *
	 * \param windowPos ������ʂ̍���̍��W
	 * \param cameraPos �J�����̍��W(��{�I��0,0)
	 */
	void Render(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	void StandardRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);
	void ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);
	void FrontRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	int GetChipSize_H() { return _chipSize_H; }
	int GetChipSize_W() { return _chipSize_W; }

	Vector2 GetPlayerStartPosition(int playerno);
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
	St::EnemyPatrol FindPatrol(int id);
	std::vector<int> CheckHitChipNo(int x, int y);
	bool IsHit(Actor& o);
	bool IsHitBarrier(int objectstage, Actor& o, int playerno);


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

	/*���}�b�v�f�[�^ [layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapTileData;
	/*��O�}�b�v�f�[�^[layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapFrontTileData;
	/*�~�j�}�b�v�f�[�^ [line][plot]*/
	std::vector<std::vector<Vector2>> _minimapData;
	/*�v���C���[�����ʒu�f�[�^[player1��2] */
	std::unordered_map<int,Vector2> _playerStart;
	/*HP�A�C�e���f�[�^ [�z�u����]*/
	std::vector<Vector2> _hpItems;
	/*�e��A�C�e���f�[�^[�z�u����]*/
	std::vector<Vector2> _bulletItems;
	/*�ʏ�G�l�~�[�f�[�^[�z�u����]*/
	std::vector<St::EnemyData> _enemyDataList;
	/*�ʏ�G�l�~�[B�f�[�^[�z�u����]*/
	std::vector<St::EnemyBData> _enemyBDataList;

	/*�G�l�~�[�̏��񃋁[�g*/
	std::unordered_map<int, St::EnemyPatrol> _patrolPoints;
	/*�}�b�v���Ƃ̏d�v�G�l�~�[���񃋁[�g*/
	std::vector<St::EnemyPatrol> _patrolPointsVIP;
	/*�T�[�o�[�f�[�^[�z�u����]*/
	std::vector<St::ServerMachineData> _serverMachineDataList;
	/*�z�u���C�g�f�[�^<ID,stats>*/
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _lightDataList;
	/*�e���|�[�^�[�����f�[�^*/
	std::vector<St::teleporterData> _teleporterInDataList;
	/*�e���|�[�^�[�o���f�[�^<ID,<���W,�����_���t���O>>*/
	std::unordered_map<int, std::pair<Vector2,bool>> _teleporterOutDataList;
	/*�X�C�b�`�f�[�^*/
	std::vector<St::SwitchData> _switchDataList;
	/*�h�A�f�[�^*/
	std::vector<std::pair<int,Vector2>> _doorDataList;
	/*TNT�f�[�^*/
	std::vector<std::pair<int, Vector2>> _tNTDataList;
	/*Mine�f�[�^*/
	std::vector<St::MineData> _mineDataList;
	
	/*�}�b�v�`�b�v�̃O���t�B�b�N�n���h���p�R���e�i*/
	/*[�^�C���p�摜�̖�����][�摜�𕪊������ۂ̃`�b�v�摜�̐�]*/
	std::vector<std::vector<int>> _cgChip;

	/*�e�}�b�v�^�C���Z�b�g�̂����蔻���ۑ�����R���e�i*/
	std::vector<std::vector<bool>> _chipCollision;

	/*��O�`�悷��^�C����gid��ۑ�*/
	std::vector<int> _gidFront;

	/*�e�N���X���ݒ肳��Ă���^�C��(gid)��ۑ�*/
	std::vector<int> _gidEnemy;
	std::vector<St::EnemyBData> _gidEnemyB;
	std::vector<int> _gidBarrier1;
	std::vector<int> _gidBarrier2;
	std::vector<int> _gidItemAmmo;
	std::vector<int> _gidItemHP;
	std::vector<int> _gidPlayer;
	std::vector<St::ServerTileData> _gidServer;
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _gidLight;
	std::unordered_map<int, bool> _gidteleportOut;//<bool�̓����_���Ƀ��[�v����t���O
	std::unordered_map<int, bool> _gidteleportIn;//<bool�̓����_�����I�ɎQ������t���O
	std::vector<int> _gidSwitch;
	std::vector<int> _gidDoor;
	std::vector<int> _gidTNT;
	std::vector<int> _gidMine;
};