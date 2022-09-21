#pragma once
#include "UIBase.h"

class Actor;
class SplitWindow;

class ButtonIcon :public UIBase{
public:
	ButtonIcon(Game&,ModeBase&, SplitWindow& window, Vector2 pos,Vector2 size,int playerno);
	Type GetType()override { return Type::ButtonIcon; }
	void Update()override;
	void Render()override;
private:
	int _cg_A, _cg_B, _cg_X,_cg_Y;
	int _playerno;
	Actor* _owner;
	int _font;
	std::string _message;
};
