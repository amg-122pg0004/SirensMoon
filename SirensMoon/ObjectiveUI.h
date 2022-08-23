#pragma once
#include "UIBase.h"

class ObjectiveUI :public UIBase {

public:
	ObjectiveUI(Game&,ModeBase&,Vector2,Vector2);
	Type GetType() { return Type::ObjectiveUI; }
	void Update()override;
	void Render()override;
	void ChangeMessage(std::string next);

private:
	std::string _message;
	std::string _nextMessage;
	Vector2 _startPos;
	int _font;
	int _cg2;
};
