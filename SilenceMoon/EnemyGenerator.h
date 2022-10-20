/*****************************************************************//**
 * \file   EnemyGenerator.h
 * \brief  敵をランダム生成するためのクラスです。
 *
 * \author 土居将太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include <vector>
#include <memory>

class EnemyGenerator {
public:
	struct EnemyPattern
	{
		int head;
		int body;
		int foot;
	};

	EnemyGenerator(EnemyPattern maxnum );
	~EnemyGenerator();
	void Init();
	/*配列からEnemyPatternを順番に返す*/
	EnemyPattern GetEnemyPattern();
	/*配列からEnemyPatternを順番に返し、返した値は配列から削除*/
	EnemyPattern GetEnemyVIPPattern();
	/*配列からEnemyPatternを順番に返す*/
	int* GetEnemyALLPatternArray() ;
	/*_enemyAllPatternをセット*/
	void SetEnemyALLPatternArray(int data[255]);

private:
	/*各部最大何通り存在するか*/
	EnemyPattern _numberOfTypes;
	/*全通りの組み合わせ*/
	std::vector<EnemyPattern> _enemyAllPattern;
	/*最後に何番目のデータを参照したか？*/
	int _lastGet;
	int _arrayData[255];
};