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
	/*�T�[�o�[���N�����邩�̔���Ɏg�p*/
	int _energy;

	/*1��,2�E,3��,4��*/
	ServerMachineData _serverData;

	int _cg_up;
	int _cg_right;
	int _cg_down;
	int _cg_left;

	EnemyGenerator::EnemyPattern _pattern;

	AABB _accessArea;

	/*�A�N�V�����\*/
	bool _accessible;
	/*true�̊ԏd�v�F���l���o��������*/
	bool _valid;

	/*�d�v�F���l��|������*/
	bool _deadVIP;

	std::shared_ptr<InputManager> _inputManager;
};
