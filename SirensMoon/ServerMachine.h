#pragma once
#include "Actor.h"
#include "ObjectDataStructs.h"
#include "EnemyGenerator.h"

class Game;
class ModeGame;
class InputManager;

class ServerMachine :public Actor {
public:
	ServerMachine(Game& game, ModeGame& mode, ServerMachineData data, EnemyGenerator::EnemyPattern grData);
	Type GetType() { return Type::Server; }
	void Update()override;
	void ChangeValidFlag(bool);
	void SetValidFlag(bool flag) { _valid = flag; }
	bool GetValidFlag() { return _valid; }
	int GetEnergy() { return _energy; }
	EnemyGenerator::EnemyPattern GetPattern() { return _pattern; }
	AABB GetAccessArea() { return _accessArea; }
	bool GetAccesible() { return _accessible; }
	void SpawnEnemyVIP();
	void DeadEnemyVIP();
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
private:
	/*サーバーが起動するかの判定に使用*/
	int _energy;

	/*1上,2右,3下,4左*/
	ServerMachineData _serverData;

	int _cg_up;
	int _cg_right;
	int _cg_down;
	int _cg_left;

	EnemyGenerator::EnemyPattern _pattern;

	AABB _accessArea;

	/*アクション可能*/
	bool _accessible;
	/*trueの間重要宇宙人を出現させる*/
	bool _valid;

	/*重要宇宙人を倒したか*/
	bool _deadVIP;

	std::shared_ptr<InputManager> _inputManager;
};
