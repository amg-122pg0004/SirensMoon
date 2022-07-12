#pragma once
#include "UIBase.h"

class Game;
class ModeBase;

class MiniMap :public UIBase{
public:
	MiniMap(Game&,ModeBase&,Vector2 pos,Vector2 size);
	~MiniMap();
	void Update() override;
	void Render() override;
private:
	int _cg_player;//<�v���C���[���ʒu�摜
	int _cg_map;//�~�j�}�b�v���摜
};
