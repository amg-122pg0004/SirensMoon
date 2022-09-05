#include "BossGimmickController.h"
#include "ObjectDataStructs.h"
#include "BigGun.h"
#include "BigGenerator.h"
#include "BigServer.h"
#include "ModeGame.h"
#include "Boss.h"
#include "MapChip.h"
#include "FX_Thunder.h"
#include "ObjectiveUI.h"
#include <algorithm>
#include <random>
#include <numeric>

BossGimmickController::BossGimmickController(Game& game, ModeGame& mode, ObjectDataStructs::BossGimmickControllerData data)
	:Actor(game,mode), _index{0},_phase1{false}, _phase2{false}, _readyRailgun{false}
{
	_gun = data.gunID;
	_generators = data.generatorsID;
	_servers = data.serversID;
	_teleport = data.teleporterID;
	_pos = data.pos;
	CheckRoomPosition();
	_size = { 100,100 };
	_collision.min = _pos - _size/2;
	_collision.max = _pos + _size/2;

	std::vector<int> v_teleport = { _teleport };
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			dynamic_cast<Gimmick&>(*actor).RecieveCall(v_teleport, false);
		}
	}

	auto v_BigGen = _mode.GetMapChips()->GetBigGeneratorData();
	for (auto BigGen : v_BigGen) {
		auto biggen = std::make_unique<BigGenerator>(_game, _mode, BigGen,*this);
		_mode.GetActorServer().Add(std::move(biggen));
	}

	auto v_BigServer = _mode.GetMapChips()->GetBigServerData();
	for (auto a_BigServer : v_BigServer) {
		auto bigserver = std::make_unique<BigServer>(_game, _mode, a_BigServer);
		_mode.GetActorServer().Add(std::move(bigserver));
	}

	auto v_BigGun = _mode.GetMapChips()->GetBigGunDataList();
	for (auto a_BigGun : v_BigGun) {
		auto biggun = std::make_unique<BigGun>(_game, _mode, a_BigGun, *this);
		_mode.GetActorServer().Add(std::move(biggun));
	}
	/*ボス生成*/
	_mode.GetActorServer().Add(std::make_unique<Boss>(_game, _mode, *this));
}

void BossGimmickController::Update() {
	if (_phase1) {
		return;
	}
	/*
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
			if (Intersect(_collision, actor->GetCollision())) {
				BossSpawn();
				_phase1 = true;
			}
		}
	}
	*/
}

void BossGimmickController::BossSpawn() {


}

void BossGimmickController::PrePhase2() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigServer) {
				Vector2 fix{50,-90};
				Vector2 pos=actor->GetPosition();
				_mode.GetActorServer().Add(std::make_unique<FX_Thunder>(_game, _mode, pos+fix,_game.GetFrameCount()));
				_mode.GetActorServer().Add(std::make_unique<FX_ThunderRing>(_game, _mode, pos + fix, _game.GetFrameCount()));
			}
		}
	}
}

void  BossGimmickController::Phase2() {
	GeneratePattern();
	DistributePattern();

	std::vector<int> v_teleport = { _teleport };
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			dynamic_cast<Gimmick&>(*actor).RecieveCall(v_teleport, true);
		}
	}
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigServer) {
				dynamic_cast<Gimmick&>(*actor).SetActivate();
			}
		}
	}
	dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
		->ChangeMessage("正しい順番で発電機を起動せよ", 1);
	dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetObjectiveUI()
		->ChangeMessage("発電機を起動する順番を\nサーバーから読み取れ", 1);
}

void BossGimmickController::GeneratePattern(){
	std::vector<int> pattern = { 0,1,2,3 };

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(pattern.begin(), pattern.end(), engine);
	_pattern = pattern;
}

void BossGimmickController::DistributePattern() {
	int i = 0;
	std::vector<int> randombox{0,1,2,3};
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(randombox.begin(), randombox.end(), engine);

	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigGenerator) {
				int random_index = randombox[i];
				dynamic_cast<BigGenerator&>(*actor).SetPattern(_pattern[random_index], GetSignal(_pattern[random_index]));
				++i;
			}
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigServer) {
				dynamic_cast<BigServer&>(*actor).SetPattern(_pattern);
				++i;
			}
			//dynamic_cast<Gimmick&>(*actor).RecieveCall(_gun, 1);
		}
	}
}

void BossGimmickController::RecieveStartGenerator(int no) {

	if (_readyRailgun) {
		return;
	}

	if (_pattern[_index] == no) {
		++_index;
		if (_index >= 4) {
			for (auto&& actor : _mode.GetObjects()) {
				if (actor->GetType() == Type::Gimmick) {
					if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigGun) {
						dynamic_cast<BigGun&>(*actor).SetAccesible();
						_readyRailgun = true;
						dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
							->ChangeMessage("巨大レールガンに乗り込み\nミッションを完遂せよ", 1);
					}
				}
			}
		}
	}
	else {
		_index = 0;
		GeneratePattern();
		DistributePattern();
	}
}
