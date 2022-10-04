/*****************************************************************//**
 * \file   DegitalLetter.h
 * \brief  ���b�Z�[�W��\������M�~�b�N
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class DegitalLetter :public Gimmick {
public:

	DegitalLetter(Game& game, ModeGame& mode, DigitalLetterData data);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::DegitalLetter; }
	void Update()override;
	void StandardRender(Vector2,Vector2)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos);
	bool GetAccessible1() { return _accessible1; }
	bool GetAccessible2() { return _accessible2; }
private:
	std::string _message;
	int _image;
	AABB _accessArea;
	std::vector<int> _cg;
	int _animNo;
	/*�A�N�Z�X�\��*/
	bool _accessible1, _accessible2;
};