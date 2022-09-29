/*****************************************************************//**
 * \file   MiniShuttle.h
 * \brief	ボス戦で使用するミニシャトルオブジェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Gimmick.h"
#include "SquareLight.h"

class BossGimmickController;

class MiniShuttle :public Gimmick {
public:
	MiniShuttle(Game& game, ModeGame& mode, BossGimmickController& controller,Vector2 pos, bool landing);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::MiniShuttle; }
	void Update();
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;
	bool GetAccessible() { return _accessible; }

	/*アニメーション再生、逆再生のセット*/
	void SetAnimation(bool inverse) { _inverse = inverse; }

private:
	bool CheckOverlapAccessArea();
	void CollisionUpdate();
	void UpdateAnimation();
	void UpdateInverseAnimation();

	BossGimmickController& _controller;
	bool _landing;
	bool _noCollision;
	bool _visible;
	bool _inverse;
	bool _cg2Flag;
	std::vector<int> _cg,_cg2;
	int _animNo;

	bool _accessible;
	AABB _accessArea;
	AABB _collisionPreset;
};