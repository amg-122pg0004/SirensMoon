/*****************************************************************//**
 * \file   SwitchArea.cpp
 * \brief  ���񂾂�M�~�b�N���N������s���̃X�C�b�`
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#include "SwitchArea.h"
#include "ModeGame.h"

SwitchArea::SwitchArea(Game& game, ModeGame& mode, SwitchAreaData data)
	:Gimmick(game, mode, data.ID), _linkGimmiks{ data.links }, _reverse{data.Reverse}
{
	_pos = data.pos;
	_size = { 30,30 };
	_accessArea.min = _pos;
	_accessArea.max = _pos + _size;
	if (_reverse) {
		LinkGimmickActivate(false);
	}
	else {
		LinkGimmickActivate(true);
	}

}

void SwitchArea::Update() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA|| actor->GetType() == Type::PlayerB) {
			if (Intersect(_accessArea, actor->GetCollision())) {
				if (_reverse) {
					LinkGimmickActivate(true);
				}
				else {
					LinkGimmickActivate(false);
				}
			}
		}
	}
}

void SwitchArea::LinkGimmickActivate(bool flag) {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			dynamic_cast<Gimmick&>(*actor).RecieveCall(_linkGimmiks, flag);
		}
	}
}

void SwitchArea::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_accessArea.Draw2(window_pos, camera_pos);
}