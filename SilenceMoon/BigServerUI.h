#pragma once
#include "UIBase.h"

class BigServer;
class SplitWindow;

class BigServerUI :public UIBase {
public:
	BigServerUI(Game&, ModeBase&, SplitWindow& window, Vector2 pos, Vector2 size,BigServer& owner);
	Type GetType()override { return Type::BigServerUI; }
	void Update();
	void Render();

private:
	int _cg_gun;
	std::vector<int> _pattern;
	int _font;
	BigServer& _owner;
	const std::vector<std::string> _text = {
		{"・・ーー・"},
		{"ーー・ーー"},
		{"ーー・・・"},
		{"・・・・・"}
	};
};
