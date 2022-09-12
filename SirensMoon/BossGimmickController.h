#pragma once
#include "Actor.h"
#include "ObjectDataStructs.h"
#include <vector>

class BossGimmickController:public Actor{
public:
	BossGimmickController(Game& game,ModeGame& mode, BossGimmickControllerData data);
	std::vector<int> GetPattern() { return _pattern; }

	Type GetType()override { return Type::BossGimmickController; }

	void Update() override;

	/*ボスの生成*/
	void BossSpawn();
	/*フェイズ2移行直前*/
	void PrePhase2();
	/*フェイズ2移行時*/
	void Phase2();
	/*パターンの生成*/
	void GeneratePattern();
	/*パターン情報の配布*/
	void DistributePattern();

	/*発電機が起動された際に呼ばれる関数*/
	void RecieveStartGenerator(int no);
	void SpawnMiniShuttle();

private:

	int _index;//<発電機進行状況
	std::vector<int> _pattern;//<パターン

	bool _phase1;
	bool _phase2;
	bool _readyRailgun;

	/*各ギミックのID*/
	int _gun;
	int _teleport;
	std::vector<int> _servers;
	std::vector<int> _generators;

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