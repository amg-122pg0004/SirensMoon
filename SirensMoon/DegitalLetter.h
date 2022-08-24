#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class DegitalLetter :public Gimmick {
public:

	DegitalLetter(Game& game, ModeGame& mode, ObjectDataStructs::DegitalLetterData data);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType() override { return GimmickType::DegitalLetter; }
	void Update()override;
	void StandardRender(int,Vector2,Vector2)override;
	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);

private:
	std::string _message;
	AABB _accessArea;

};