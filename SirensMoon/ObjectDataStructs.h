#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Math.h"


class ObjectDataStructs{
public:
	/*エネミーデータ構造*/
	struct EnemyData {
		int ID;
		int	Enemytype;
		Vector2 StartPosition;
		int patrolID;
	};

	/*エネミーBデータ構造*/
	struct EnemyBData {
		int ID;
		Vector2 StartPosition;
		std::vector<int> Direction;//<見る角度
		std::vector<int> LooiTime;//<各角度を見る時間
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

	/*Mineデータ構造*/
	struct MineData {
		int ID;
		Vector2 pos;
		int dir;
	};
};
