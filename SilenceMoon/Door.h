/*****************************************************************//**
 * \file   Door.h
 * \brief  開くドアのギミック
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Door:public Gimmick{
public:
	Door(Game& game, ModeGame& mode, DoorData data);
	void Update() override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;

	bool RecieveCall(std::vector<int> IDs, bool flag)override;
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::Door; }
private:
	int _partNo;
	/*アクティブ、非アクティブ時画像*/
	int _cg2, _cg3;
};
