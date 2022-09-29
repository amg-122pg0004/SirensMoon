/*****************************************************************//**
 * \file   BigGenerator.h
 * \brief  ボスギミックを作動させるための
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class BossGimmickController;

class BigGenerator :public Gimmick {
public:
	BigGenerator(Game& game, ModeGame& mode, BigGeneratorData data, BossGimmickController& controller);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::BigGenerator; }
	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos);
	bool GetSignalActive() { return _flash; };
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
	void UpdateCollsiion();
	void SetPattern(int pattern,std::vector<bool> signal);
	bool GetAccessible() { return _accessible; }
private:

	bool CheckHitBullet();

	bool _flash;//<発光するタイミング

	/*単符表示フレーム数*/
	int _span;
	/*現在の表示フレーム数*/
	int _elapsed;

	/*現在表示中の点滅項番*/
	int _index;
	/*Generatorが使用するライト点滅パターン*/
	std::vector<bool> _signal;
	/*パターン項番*/
	int _pattern;

	/*コントローラーの参照*/
	BossGimmickController& _controller;

	int _cg_active, _cg_passive;

	AABB _accessArea;
	bool _accessible;
};