#include "BossGimmickController.h"
#include "BigGun.h"
#include "BigGenerator.h"
#include "BigServer.h"
#include "ModeGame.h"
#include <algorithm>
#include <random>
#include <numeric>

BossGimmickController::BossGimmickController(ModeGame& mode)
	:_mode{mode}, _gun{nullptr}, _index{0}
{
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigGun) {
				_gun = actor.get();
			}
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigGenerator) {
				_generators.emplace_back(actor.get());
			}
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigServer) {
				_servers.emplace_back(actor.get());
			}
		}
	}
}

void BossGimmickController::GeneratePattern(){
	std::vector<int> pattern = { 1,2,3,4 };

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(pattern.begin(), pattern.end(), engine);
	_pattern = pattern;
}

void BossGimmickController::DistributePattern() {
	for (auto&& server : _servers) {
		dynamic_cast<BigServer*>(server)->SetPattern(_pattern);
	}
	int i = 0;
	for (auto&& generator : _generators) {
		dynamic_cast<BigGenerator*>(generator)->SetPattern(_pattern[i], GetSignal(_pattern[i]));
		++i;
	}
}

void BossGimmickController::RecieveStartGenerator(int no) {
	if (_pattern[_index] == no) {
		++_index;
		if (_index >= 4) {
			dynamic_cast<BigGun*>(_gun)->SetAccesible();
		}
	}
	else {
		_index = 0;
		GeneratePattern();
		DistributePattern();
	}
}
