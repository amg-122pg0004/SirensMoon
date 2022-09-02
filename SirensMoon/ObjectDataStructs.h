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

	/*エネミーデータ構造*/
	struct EnemyData {
		int ID;
		Vector2 StartPosition;
		int patrolID;
		int waitFrame;
	};

	/*エネミーBデータ構造*/
	struct EnemyBData {
		int ID;
		Vector2 StartPosition;
		std::vector<int> Direction;//<見る角度
		std::vector<int> LookTime;//<各角度を見る時間
	};

	/*エネミー巡回経路データ構造*/
	struct EnemyPatrol {
		int ID;
		std::vector<Vector2> PatrolPoints;
		bool TruckingMode{ false };
	};

	/*サーバーデータ構造*/
	struct ServerMachineData {
		Vector2 Position;
		std::string Direction;
	};

	/*サーバータイルセットデータ構造*/
	struct ServerTileData {
		int gid;
		std::string Direction;
	};

	/*テレポーター(in)データ構造*/
	struct teleporterData {
		int ID;
		Vector2 pos;
		bool random;
		int tereortID;
	};

	/*スイッチデータ構造*/
	struct SwitchData {
		int ID;
		Vector2 pos;
		std::vector<int> links;
	};

	/*スイッチエリアデータ構造*/
	struct SwitchAreaData {
		int ID;
		Vector2 pos;
		std::vector<int> links;
	};

	/*Doorデータ構造*/
	struct DoorData {
		int ID;
		Vector2 pos;
		int PartNo;
	};

	/*TNTデータ構造*/
	struct TNTData {
		int ID;
		Vector2 pos;
		int CG;
	};

	/*Mineデータ構造*/
	struct MineData {
		int ID;
		Vector2 pos;
		int range;
		int dir;
	};

	/*ScreenPumpデータ構造*/
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