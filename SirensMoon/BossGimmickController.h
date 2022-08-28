#pragma once
#include "Actor.h"
#include "ObjectDataStructs.h"
#include <vector>

class BossGimmickController:public Actor{
public:
	BossGimmickController(Game& game,ModeGame& mode, ObjectDataStructs::BossGimmickControllerData data);
	std::vector<int> GetPattern() { return _pattern; }

	Type GetType()override { return Type::BossGimmickController; }

	void Update() override;

	/*ボスの生成*/
	void BossSpawn();
	/*パターンの生成*/
	void GeneratePattern();
	/*パターン情報の配布*/
	void DistributePattern();

	/*発電機が起動された際に呼ばれる関数*/
	void RecieveStartGenerator(int no);
	

private:
	int _index;//<発電機進行状況
	std::vector<int> _pattern;//<パターン

	bool _phase1;
	bool _phase2;

	/*各ギミックのポインタ*/
	Actor* _gun;
	std::vector<Actor*> _servers;
	std::vector<Actor*> _generators;

	static const std::vector<bool> GetSignal(int index) {
		static const std::vector<std::vector<bool>> signal = {
			{1,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,},
			{1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,0,0,},
			{1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,0},
			{1,0,1,0,1,0,1,0,1,0,0,0,}
		};
		return signal[index];
	}
};