#pragma once
#include "UIBase.h"
//#include "InputManager.h"
#include <memory>

class Game;
class ModeBase;
class InputManager;

class MiniMap :public UIBase{
public:
	MiniMap(Game&,ModeBase&,Vector2 pos,Vector2 size);
	~MiniMap();
	void Update() override;
	void Render() override;

private:
	std::shared_ptr<InputManager> _inputManager;
	int _cg_player;//<�v���C���[���ʒu�摜
	int _cg_map;//�~�j�}�b�v���摜
	bool _visible;
};
