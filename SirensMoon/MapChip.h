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
	 * \brief �^�C���̕\�����s���֐�
	 *
	 * \param windowPos ������ʂ̍���̍��W
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
	 * \brief �}�b�v�`�b�v�ƃA�N�^�[�̐ڐG����
	 * 
	 * \param col �A�N�^�[�̃R���W�����{�b�N�X
	 * \param backlayer�@true�Ȃ��냌���_�����O�}�b�v�`�b�v�Ƃ̔�����Ƃ�
	 * \return ����������true
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
	/*���}�b�v�f�[�^ [layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapBackTileData;
	/*���ԃ}�b�v�f�[�^ [layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapTileData;
	/*��O�}�b�v�f�[�^[layer][y][x]*/
	std::vector<std::vector<std::vector<int>>> _mapFrontTileData;
	/*�~�j�}�b�v�f�[�^ [line][�F,plot]*/
	std::vector<std::pair<unsigned int,std::vector<Vector2>>> _minimapData;
	/*�v���C���[�����ʒu�f�[�^[player1��2] */
	std::unordered_map<int,PlayerData> _playerData;
	/*HP�A�C�e���f�[�^ [�z�u����]*/
	std::vector<Vector2> _hpItems;
	/*�e��A�C�e���f�[�^[�z�u����]*/
	std::vector<Vector2> _bulletItems;
	/*�ʏ�G�l�~�[�f�[�^[�z�u����]*/
	std::vector<EnemyData> _enemyDataList;
	/*�ʏ�G�l�~�[B�f�[�^[�z�u����]*/
	std::vector<EnemyBData> _enemyBDataList;

	/*�G�l�~�[�̏��񃋁[�g*/
	std::unordered_map<int, EnemyPatrol> _patrolPoints;
	/*�}�b�v���Ƃ̏d�v�G�l�~�[���񃋁[�g*/
	std::vector<EnemyPatrol> _patrolPointsVIP;
	/*�T�[�o�[�f�[�^[�z�u����]*/
	std::vector<ServerMachineData> _serverMachineDataList;
	/*�z�u���C�g�f�[�^<ID,stats>*/
	std::vector<std::pair<int,SquareLightStats>> _lightDataList;
	/*�e���|�[�^�[�����f�[�^*/
	std::vector<teleporterData> _teleporterInDataList;
	/*�e���|�[�^�[�o���f�[�^<ID,<���W,�����_���t���O>>*/
	std::unordered_map<int, std::pair<Vector2,bool>> _teleporterOutDataList;
	/*�X�C�b�`�f�[�^*/
	std::vector<SwitchData> _switchDataList;
	/*�X�C�b�`�G���A�f�[�^*/
	std::vector<SwitchAreaData> _switchAreaDataList;
	/*�h�A�f�[�^*/
	std::vector<DoorData> _doorDataList;
	/*TNT�f�[�^*/
	std::vector<TNTData> _tNTDataList;
	/*Mine�f�[�^*/
	std::vector<MineData> _mineDataList;
	/*ScreenPump�f�[�^*/
	std::vector<ScreenPumpData> _screenPumpDataList;
	/*StickyBomb�f�[�^*/
	std::vector<StickyBombData> _stickyBombDataList;
	/*BrakableObject�f�[�^*/
	std::vector<BreakableObjectData> _breakableObjectData;
	/*DegitalLetter�f�[�^*/
	std::vector<DigitalLetterData> _deditalLetterData;
	/*BigServerData�f�[�^*/
	std::vector<BigServerData> _bigServerDataList;
	/*BigGeneratorData�f�[�^*/
	std::vector<BigGeneratorData> _bigGeneratorDataList;
	/*BossGimmickControllerData�f�[�^*/
	std::vector<BossGimmickControllerData> _bossGimmickControllerDataList;
	/*BossGimmickControllerData�f�[�^*/
	std::vector<BigGunData> _bigGunDataList;

	
	/*�}�b�v�`�b�v�̃O���t�B�b�N�n���h���p�R���e�i*/
	/*[�^�C���p�摜�̖�����][�摜�𕪊������ۂ̃`�b�v�摜�̐�]*/
	std::vector<std::vector<int>> _cgChip;

	/*�����蔻�肪�ݒ肳��Ă���^�C����GID��ۑ�����R���e�i*/
	std::vector<int> _chipCollision;

	/*��O�`�悷��^�C����gid��ۑ�*/
	std::vector<int> _gidFront;
	/*���`�悷��^�C����gid��ۑ�*/
	std::vector<int> _gidBack;

	/*�e�N���X���ݒ肳��Ă���^�C��(gid)��ۑ�*/
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
	std::unordered_map<int, bool> _gidteleportOut;//<bool�̓����_���Ƀ��[�v����t���O
	std::unordered_map<int, bool> _gidteleportIn;//<bool�̓����_�����I�ɎQ������t���O
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