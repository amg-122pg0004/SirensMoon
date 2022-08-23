#pragma once
#include "UIBase.h"

class MessageWindow :public UIBase {
public:
	MessageWindow(Game&, ModeBase&, Vector2 pos, Vector2 size);

	void Update()override;
	void Render()override;

private:
	std::string _message;
};
