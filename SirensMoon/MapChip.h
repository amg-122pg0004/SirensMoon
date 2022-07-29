#pragma once
#include <unordered_map>
#include "picojson/picojson.h"
#include "Math.h"
#include <vector>

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
		int Direction;
	};

	MapChips(Game& game,ModeBase& mode);
	~MapChips();
	bool LoadMap(std::string folderpath, std::string filename);

	/**
	 * \brief �^�C���̕\�����s���֐�
	 *
	 * \param windowPos ������ʂ̍���̍��W
	 * \param cameraPos �J�����̍��W(��{�I��0,0)
	 */
	void Render(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	void StandardRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);
	void ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);

	int GetChipSize_H() { return _chipSize_H; }
	int GetChipSize_W() { return _chipSize_W; }

	Vector2 GetPlayerStartPosition(int playerno) { return _playerStart[0][playerno]; }
	std::vector<EnemyData> GetEnemyData() { return _enemyDataList[0]; }
	std::vector<EnemyPatrol> GetPatrolPointsVIP() { return _patrolPointsVIP; }
	std::vector<Vector2> GetHPItemData() { return _hpItems[0]; }
	std::vector<Vector2> GetBulletData() { return _bulletItems[0]; }
	std::vector<ServerMachineData> GetServerData() { return _serverMachineDataList[0]; }
	EnemyPatrol FindPatrol(int id);
	std::vector<int> CheckHitChipNo(int objectstage, int x, int y);
	bool IsHit(int objectstage, Actor& o);
	bool IsHitBarrier(int objectstage, Actor& o, int playerno);


private:
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

	/*�}�b�v�f�[�^ [stageNo][layer][y][x]*/
	std::vector<std::vector<std::vector<std::vector<int>>>> _mapDataStandard;
	/*�~�j�}�b�v�f�[�^ [y][x]*/
	std::vector<std::vector<std::vector<Vector2>>> _mapDataRecon;
	/*�}�b�v���Ƃ̃v���C���[�f�[�^ [stageNo][player1��2]*/
	std::vector<std::vector<Vector2>> _playerStart;
	/*�}�b�v���Ƃ�HP�A�C�e���f�[�^ [stage][�z�u����]*/
	std::vector<std::vector<Vector2>> _hpItems;
	/*�}�b�v���Ƃ̒e��A�C�e���f�[�^[stage][�z�u����]*/
	std::vector<std::vector<Vector2>> _bulletItems;

	/*�}�b�v���Ƃ̒ʏ�G�l�~�[�f�[�^[stage][�z�u����]*/
	std::vector<std::vector<EnemyData>> _enemyDataList;
	/*�}�b�v���Ƃ̃G�l�~�[�̏��񃋁[�g*/
	std::unordered_map<int, EnemyPatrol> _patrolPoints;
	/*�}�b�v���Ƃ̏d�v�G�l�~�[���񃋁[�g*/
	std::vector<EnemyPatrol> _patrolPointsVIP;
	/*�}�b�v���Ƃ̃T�[�o�[�f�[�^[stage][�z�u����]*/
	std::vector<std::vector<ServerMachineData>> _serverMachineDataList;
	
	/*�}�b�v�`�b�v�̃O���t�B�b�N�n���h���p�R���e�i*/
	/*[�^�C���p�摜�̖�����][�摜�𕪊������ۂ̃`�b�v�摜�̐�]*/
	std::vector<std::vector<int>> _cgChip;
	/*�e�}�b�v�`�b�v�̂����蔻���ۑ�����R���e�i*/
	std::vector<std::vector<bool>> _chipCollision;

	/*�e�N���X���ݒ肳��Ă���gid*/
	std::vector<int> _gidEnemy;
	std::vector<int> _gidBarrier;
	std::vector<int> _gidItemAmmo;
	std::vector<int> _gidItemHP;
	std::vector<int> _gidPlayer;
	std::vector<int> _gidServer;
};