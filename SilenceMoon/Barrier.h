/*****************************************************************//**
 * \file   Barrier.h
 * \brief  バリアギミックのクラス
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/

#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Barrier :public Gimmick {
public:
	Barrier(Game& game, ModeGame& mode, BarrierData data);
	void Update() override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Gimmick; }

protected:
	std::pair<int, int> _cg;
	double _animSpeed;
	int _alpha;
};

class BarrirA:public Barrier{
public:
	BarrirA(Game& game, ModeGame& mode, BarrierData data);
	GimmickType GetGimmickType()override { return GimmickType::BarrierA; }
};

class BarrirB :public Barrier {
public:
	BarrirB(Game& game, ModeGame& mode, BarrierData data);
	GimmickType GetGimmickType()override { return GimmickType::BarrierB; }
};