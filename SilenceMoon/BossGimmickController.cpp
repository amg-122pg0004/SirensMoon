/*****************************************************************//**
 * \file   BossGimmickController.h
 * \brief  ボスと関連ギミック、イベントを操作するクラス
 *
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
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
#include "SplitWindow.h"
#include "MiniMap.h"
#include "MiniShuttle.h"
#include "PlayerA.h"
#include <algorithm>
#include <random>
#include <numeric>

BossGimmickController::BossGimmickController(Game& game, ModeGame& mode, BossGimmickControllerData data)
	:Actor(game, mode), _index{ 0 }, _phase1{ false }, _phase2{ false }, _readyRailgun{ false }
{
	_gun = data.gunID;
	_pos = data.pos;
	CheckRoomPosition();
	_size = { 100,100 };
	_collision.min = _pos - _size / 2;
	_collision.max = _pos + _size / 2;

	auto v_BigGen = _mode.GetMapChips()->GetBigGeneratorData();
	for (auto BigGen : v_BigGen) {
		auto biggen = std::make_unique<BigGenerator>(_game, _mode, BigGen, *this);
		_generators.push_back(biggen.get());
		_mode.GetActorServer().Add(std::move(biggen));
	}

	auto v_BigServer = _mode.GetMapChips()->GetBigServerData();
	for (auto a_BigServer : v_BigServer) {
		auto bigserver = std::make_unique<BigServer>(_game, _mode, a_BigServer);
		_servers.push_back(bigserver.get());
		_mode.GetActorServer().Add(std::move(bigserver));
	}

	auto v_BigGun = _mode.GetMapChips()->GetBigGunDataList();
	for (auto a_BigGun : v_BigGun) {
		auto biggun = std::make_unique<BigGun>(_game, _mode, a_BigGun, *this);

		_mode.GetActorServer().Add(std::move(biggun));
	}
	/*ボス生成*/
	_mode.GetActorServer().Add(std::make_unique<Boss>(_game, _mode, *this));

	auto&& uiserver = _mode.GetSplitWindow()[1]->GetUIServer2().GetObjects();
	for (auto&& ui : uiserver) {
		if (ui->GetType() == UIBase::Type::MiniMap) {
			dynamic_cast<MiniMap&>(*ui).SetBossFlag();
		}
	}
}

void BossGimmickController::Update() {
	if (_phase1) {
		return;
	}

}

void BossGimmickController::BossSpawn() {


}

void BossGimmickController::PrePhase2() {
	Vector2 pos = { splitscreen_W / 2, screen_H / 2 };
	_mode.GetActorServer().Add(std::make_unique<MiniShuttle>(_game, _mode, *this, pos, false));

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

	std::shuffle(_generators.begin(), _generators.end(), engine);

	for (auto&& gen : _generators) {
		gen->SetPattern(_pattern[i], GetSignal(_pattern[i]));
		++i;
	}
	for (auto&& server : _servers) {
		server->SetPattern(_pattern);
		++i;
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
						dynamic_cast<BigGun&>(*actor).SetActivate();
						_readyRailgun = true;
						dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetObjectiveUI()
							->ChangeMessage("巨大レールガンに乗り込み\nミッションを完遂せよ", 1);
						for (auto&& ui : dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[0]->GetUIServer2().GetObjects()) {
							if (ui->GetType() == UIBase::Type::RideInfo) {
								ui->SetVisibillity(true);
							}
						}
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

void BossGimmickController::SpawnMiniShuttle(){
	Vector2 pos = { splitscreen_W / 2+ splitscreen_W*3+100, screen_H / 2+ screen_H *3};
	_mode.GetActorServer().Add(std::make_unique<MiniShuttle>(_game, _mode, *this, pos,true));
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			static_cast<PlayerA&>(*actor).ChangePosition({ 3240, 4180 });
		}
	}
}

void BossGimmickController::WarpEvent(){
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			static_cast<PlayerA&>(*actor).OffMiniShuttle();
		}
	}
}