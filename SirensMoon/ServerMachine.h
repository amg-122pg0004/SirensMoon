#pragma once
#include "Actor.h"
#include "ObjectDataStructs.h"
#include "EnemyGenerator.h"

class Game;
class ModeGame;
class InputManager;

class ServerMachine:public Actor{
	public:
		ServerMachine(Game& game, ModeGame& mode, ObjectDataStructs::ServerMachineData data, EnemyGenerator::EnemyPattern grData);
		Type GetType() { return Type::Server; }
		void Update()override;
		void ChangeValidFlag(bool);
		bool GetValidFlag() { return _valid; }
		int GetEnergy() { return _energy; }
		AABB GetAccessArea() { return _accessArea; }
		void SpawnEnemyVIP();
		void DeadEnemyVIP();
		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	private:
		/*サーバーが起動するかの判定に使用*/
		int _energy;

		/*1上,2右,3下,4左*/
		ObjectDataStructs::ServerMachineData _serverData;

		int _cg_up;
		int _cg_right;
		int _cg_down;
		int _cg_left;

		EnemyGenerator::EnemyPattern _pattern;

		AABB _accessArea;
		/*アクセス可能な状態か*/
		bool _valid;

		/*重要宇宙人を倒したか*/
		bool _deadVIP;

		std::shared_ptr<InputManager> _inputManager;
};
