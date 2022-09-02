#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Math.h"


class ObjectDataStructs {
public:

	struct PlayerData {
		Vector2 StarPosition;
		double SpeedMax;
		double Accelerate;
		double Friction;
	};

	/*�G�l�~�[�f�[�^�\��*/
	struct EnemyData {
		int ID;
		Vector2 StartPosition;
		int patrolID;
		int waitFrame;
	};

	/*�G�l�~�[B�f�[�^�\��*/
	struct EnemyBData {
		int ID;
		Vector2 StartPosition;
		std::vector<int> Direction;//<����p�x
		std::vector<int> LookTime;//<�e�p�x�����鎞��
	};

	/*�G�l�~�[����o�H�f�[�^�\��*/
	struct EnemyPatrol {
		int ID;
		std::vector<Vector2> PatrolPoints;
		bool TruckingMode{ false };
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
		int ID;
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

	/*�X�C�b�`�G���A�f�[�^�\��*/
	struct SwitchAreaData {
		int ID;
		Vector2 pos;
		std::vector<int> links;
	};

	/*Door�f�[�^�\��*/
	struct DoorData {
		int ID;
		Vector2 pos;
		int PartNo;
	};

	/*TNT�f�[�^�\��*/
	struct TNTData {
		int ID;
		Vector2 pos;
		int CG;
	};

	/*Mine�f�[�^�\��*/
	struct MineData {
		int ID;
		Vector2 pos;
		int range;
		int dir;
	};

	/*ScreenPump�f�[�^�\��*/
	struct ScreenPumpData {
		int ID;
		Vector2 pos;
		int range;
		int dir;
	};

	/*StickyBomb*/
	struct StickyBombData {
		int ID;
		Vector2 pos;
		int range;
		int timer;
	};


	struct BreakableObjectData
	{
		int ID;
		Vector2 pos;
	};

	struct DegitalLetterData
	{
		int ID;
		Vector2 pos;
		std::string message;
	};

	struct BigServerData {
		int ID;
		Vector2 pos;
		std::string Direction;
	};

	struct BigGeneratorData {
		int ID;
		Vector2 pos;
	};

	struct BigGunData {
		int ID;
		Vector2 pos;
	};

	struct BossGimmickControllerData {
		int ID;
		Vector2 pos;
		int gunID;
		int teleporterID;
		std::vector<int> serversID;
		std::vector<int> generatorsID;
	};
};