#pragma once
#include "Actor.h"
#include <memory>
#include <vector>

class Game;
class ModeBase;
class InputManager;

class ServerMachine:public Actor{
	public:
		ServerMachine(Game& game, ModeBase& mode, Vector2 pos,int dir);
		Type GetType() { return Type::Server; }
		void Update()override;
		void ChangeValidFlag(bool);
		bool GetValidFlag() { return _valid; }
		AABB GetAccessArea() { return _accessArea; }
		std::vector<int> GetGeneratedEnemy() { return _generatedEnemy; }
		void GenerateEnemy();
		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	private:
		/*1��,2�E,3��,4��*/
		int _dir;

		int _cg_up;
		int _cg_right;
		int _cg_down;
		int _cg_left;

		std::vector<int> _generatedEnemy;

		AABB _accessArea;
		/*�A�N�Z�X�\�ȏ�Ԃ�*/
		bool _valid;

		std::shared_ptr<InputManager> _inputManager;
};
