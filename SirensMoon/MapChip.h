#pragma once
#include <unordered_map>
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>
#include "SquareLight.h"

class Game;
class ModeBase;
class SplitWindow;
class Actor;

class MapChips {
public:
	/*�G�l�~�[�f�[�^�\��*/
	struct EnemyData {
		int ID;
		int	Enemytype;
		Vector2 StartPosition;
		int patrolID;
	};

	/*�G�l�~�[����o�H�f�[�^�\��*/
	struct EnemyPatrol {
		int ID;
		std::vector<Vector2> PatrolPoints;
		bool TruckingMode{false};
	};

	/*�T�[�o�[�f�[�^�\��*/
	struct ServerMachineData {
		Vector2 Position;
		std::string Direction;
	};

	/*�T�[�o�[�^�C���Z�b�g�f�[�^�\��*/
	struct ServerTileData {
		int gid;
		std::string Direction;
	};

	/*�e���|�[�^�[(in)�f�[�^�\��*/
	struct teleporterData {
		Vector2 pos;
		bool random;
		int tereortID;
	};

	/*�X�C�b�`�f�[�^�\��*/
	struct SwitchData {
		int ID;
		Vector2 pos;
		std::vector<int> links;
	};

	/*Mine�f�[�^�\��*/
	struct MineData {
		int ID;
		Vector2 pos;
		int dir;
	};


	MapChips(Game& game,ModeBase& mode);
	~MapChips();


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
	std::vector<EnemyData> GetEnemyData() { return _enemyDataList; }
	std::vector<EnemyPatrol> GetPatrolPointsVIP() { return _patrolPointsVIP; }
	std::vector<Vector2> GetHPItemData() { return _hpItems; }
	std::vector<Vector2> GetBulletData() { return _bulletItems; }
	std::vector<ServerMachineData> GetServerData() { return _serverMachineDataList; }
	std::vector<std::pair<int,SquareLight::SquareLightStats>> GetLightData() { return _lightDataList; }
	std::vector<teleporterData> GetteleporterInData() { return _teleporterInDataList; }
	std::unordered_map<int, std::pair<Vector2, bool>> GetteleporterOutData() { return _teleporterOutDataList; }
	std::vector<SwitchData> GetSwitchData() { return _switchDataList; }
	std::vector<std::pair<int, Vector2>>GetDoorData() { return _doorDataList; }
	std::vector<std::pair<int, Vector2>>GetTNTData() { return _tNTDataList; }
	std::vector<MineData> GetMineData() { return _mineDataList; }
	EnemyPatrol FindPatrol(int id);
	std::vector<int> CheckHitChipNo(int objectstage, int x, int y);
	bool IsHit(int objectstage, Actor& o);
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
	std::vector<EnemyData> _enemyDataList;
	/*�G�l�~�[�̏��񃋁[�g*/
	std::unordered_map<int, EnemyPatrol> _patrolPoints;
	/*�}�b�v���Ƃ̏d�v�G�l�~�[���񃋁[�g*/
	std::vector<EnemyPatrol> _patrolPointsVIP;
	/*�T�[�o�[�f�[�^[�z�u����]*/
	std::vector<ServerMachineData> _serverMachineDataList;
	/*�z�u���C�g�f�[�^<ID,stats>*/
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _lightDataList;
	/*�e���|�[�^�[�����f�[�^*/
	std::vector<teleporterData> _teleporterInDataList;
	/*�e���|�[�^�[�o���f�[�^<ID,<���W,�����_���t���O>>*/
	std::unordered_map<int, std::pair<Vector2,bool>> _teleporterOutDataList;
	/*�X�C�b�`�f�[�^*/
	std::vector<SwitchData> _switchDataList;
	/*�h�A�f�[�^*/
	std::vector<std::pair<int,Vector2>> _doorDataList;
	/*TNT�f�[�^*/
	std::vector<std::pair<int, Vector2>> _tNTDataList;
	/*Mine�f�[�^*/
	std::vector<MineData> _mineDataList;
	
	/*�}�b�v�`�b�v�̃O���t�B�b�N�n���h���p�R���e�i*/
	/*[�^�C���p�摜�̖�����][�摜�𕪊������ۂ̃`�b�v�摜�̐�]*/
	std::vector<std::vector<int>> _cgChip;

	/*�e�}�b�v�^�C���Z�b�g�̂����蔻���ۑ�����R���e�i*/
	std::vector<std::vector<bool>> _chipCollision;

	/*��O�`�悷��^�C����gid��ۑ�*/
	std::vector<int> _gidFront;

	/*�e�N���X���ݒ肳��Ă���^�C��(gid)��ۑ�*/
	std::vector<int> _gidEnemy;
	std::vector<int> _gidBarrier1;
	std::vector<int> _gidBarrier2;
	std::vector<int> _gidItemAmmo;
	std::vector<int> _gidItemHP;
	std::vector<int> _gidPlayer;
	std::vector<ServerTileData> _gidServer;
	std::vector<std::pair<int,SquareLight::SquareLightStats>> _gidLight;
	std::unordered_map<int, bool> _gidteleportOut;//<bool�̓����_���Ƀ��[�v����t���O
	std::unordered_map<int, bool> _gidteleportIn;//<bool�̓����_�����I�ɎQ������t���O
	std::vector<int> _gidSwitch;
	std::vector<int> _gidDoor;
	std::vector<int> _gidTNT;
	std::vector<int> _gidMine;
};