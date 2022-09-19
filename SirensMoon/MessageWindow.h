#pragma once
#include "UIBase.h"

class MessageWindow :public UIBase {
public:
	MessageWindow(Game&, ModeBase&, Vector2 pos, Vector2 size,int playerno);
	Type GetType()override { return Type::MessageWindow; }

	void Update()override;
	void Render()override;
	void SetMessage(std::string msg,int image);

private:
	std::string _message;
	int _font;
	int _playerno;
	int _alpha;

	int _imageWindow;
	int _image;
};
