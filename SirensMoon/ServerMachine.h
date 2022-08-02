#pragma once
#include "Actor.h"
#include "MapChip.h"
#include "EnemyVIP.h"
#include <memory>
#include <vector>
#include "EnemyGenerator.h"

class Game;
class ModeBase;
class InputManager;

class ServerMachine:public Actor{
	public:
		ServerMachine(Game& game, ModeBase& mode, MapChips::ServerMachineData data, EnemyGenerator::EnemyPattern pattern);
		Type GetType() { return Type::Server; }
		void Update()override;
		void ChangeValidFlag(bool);
		bool GetValidFlag() { return _valid; }
		int GetEnergy() { return _energy; }
		AABB GetAccessArea() { return _accessArea; }
		std::vector<int> GetGeneratedEnemy() { return _generatedEnemy; }
		void SpawnEnemyVIP();
		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	private:
		/*サーバーが起動するかの判定に使用*/
		int _energy;

		/*1上,2右,3下,4左*/
		MapChips::ServerMachineData _serverData;

		int _cg_up;
		int _cg_right;
		int _cg_down;
		int _cg_left;

		EnemyGenerator::EnemyPattern _enemypattern;
		std::vector<int> _generatedEnemy;

		AABB _accessArea;
		/*アクセス可能な状態か*/
		bool _valid;

		std::shared_ptr<InputManager> _inputManager;
};
