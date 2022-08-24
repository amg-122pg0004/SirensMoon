#pragma once
#include "UIBase.h"

class MessageWindow :public UIBase {
public:
	MessageWindow(Game&, ModeBase&, Vector2 pos, Vector2 size);
	Type GetType()override { return Type::MessageWindow; }

	void Update()override;
	void Render()override;
	void SetMessage(std::string msg);

private:
	std::string _message;
	int _font;
};
