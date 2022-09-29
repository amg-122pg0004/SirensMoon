/*****************************************************************//**
 * \file   BreakableObject.h
 * \brief  壊せる岩のオブジェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class BreakableObject :public Gimmick{
public:
	BreakableObject(Game&,ModeGame&,BreakableObjectData);

	void Update() override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::BreakableObject; }
};
