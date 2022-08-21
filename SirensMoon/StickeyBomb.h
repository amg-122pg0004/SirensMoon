#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Game;
class ModeGame;

class StickyBomb :public Gimmick {
public:
	StickyBomb(Game& game, ModeGame& mode, ObjectDataStructs::StickyBombData data);

	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::StickyBomb; }
	bool GetAccessible1() { return _accessible1; }
	bool GetAccessible2() { return _accessible2; }

	void Update()override;
	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

private:

	/*�������Ă���v���C���[*/
	Actor* _player;
	/*���m�͈�*/
	AABB _detectionArea;
	/*�����A�N�V�����͈�*/
	AABB _accessArea;
	/*���j�܂ł̎���*/
	int _timer;
	/*�A�N�Z�X�\��*/
	bool _accessible1, _accessible2;
};




