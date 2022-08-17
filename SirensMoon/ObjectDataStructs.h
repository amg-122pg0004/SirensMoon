#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Math.h"


class ObjectDataStructs{
public:

	struct PlayerData {
		Vector2 StarPosition;
		
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
};