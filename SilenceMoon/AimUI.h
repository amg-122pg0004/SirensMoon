#pragma once
#include "UIBase.h"
#include "InputManager.h"
#include <memory>
class SplitWindow;

class AimUI :public UIBase {
public:
	AimUI(Game&, ModeBase&,SplitWindow& window, Vector2 pos, Vector2 size);
	void Update() override;
	void Render() override;
	Type GetType()override { return Type::AimUI; }
private:
	int _cg_cursor;
	int _cg_Info;
	Vector2 _pos_cursor;
	double _speed;
	std::shared_ptr<InputManager> _inputManager;
	bool _gameClear;
	int _gameClearTimer;
};
