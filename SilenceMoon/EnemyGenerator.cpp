/*****************************************************************//**
 * \file   EnemyGenerator.cpp
 * \brief  敵をランダム生成するためのクラスです。
 *
 * \author 土居将太郎
 * \date   August 2022
 *********************************************************************/

#include "EnemyGenerator.h"
#include ""
#include <algorithm>
#include <random>
#include <numeric>

EnemyGenerator::EnemyGenerator(EnemyPattern maxnum)
	:_lastGet{ 0 }
{
	_numberOfTypes = maxnum;
	Init();
}

EnemyGenerator::~EnemyGenerator() {

}

void EnemyGenerator::Init() {
	_enemyAllPattern.clear();
	EnemyPattern pattern;
	for (int i = 1; i <= _numberOfTypes.head; ++i) {
		for (int i2 = 1; i2 <= _numberOfTypes.body; ++i2) {
			for (int i3 = 1; i3 <= _numberOfTypes.foot; ++i3) {
				pattern.head = i;
				pattern.body = i2;
				pattern.foot = i3;
				_enemyAllPattern.emplace_back(pattern);
			}
		}
	}
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(_enemyAllPattern.begin(), _enemyAllPattern.end(), engine);
}

EnemyGenerator::EnemyPattern EnemyGenerator::GetEnemyVIPPattern() {
	auto pattern = _enemyAllPattern[0];
	_enemyAllPattern.erase(_enemyAllPattern.begin());
	return pattern;
}

EnemyGenerator::EnemyPattern EnemyGenerator::GetEnemyPattern() {
	auto pattern = _enemyAllPattern[_lastGet];
	++_lastGet;
	if (_lastGet > _enemyAllPattern.size() - 1) {
		_lastGet = 0;
	}
	return pattern;
}

int* EnemyGenerator::GetEnemyALLPatternArray() {
	int output[255] = {};
	int i{ 0 };
	for (auto&& aPattern : _enemyAllPattern) {
		output[i] = aPattern.head;
		output[i + 1] = aPattern.body;
		output[i + 2] = aPattern.foot;
		i += 3;
	}
	return output;
}

/*_enemyAllPatternをセット*/
void EnemyGenerator::SetEnemyALLPatternArray(int data[255]) {

	for (int i = 0; i < 255; i += 3) {
		if (data[i] == 0) {
			break;
		}
		_enemyAllPattern[i / 3].head = data[i];
		_enemyAllPattern[i / 3].body = data[i + 1];
		_enemyAllPattern[i / 3].foot = data[i + 2];
	}
}
