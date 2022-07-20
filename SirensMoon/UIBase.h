#pragma once
#include "Math.h"

class Game;
class ModeBase;


class UIBase{
public:
	UIBase(Game&,ModeBase&,Vector2 pos,Vector2 size);
	~UIBase();
	virtual void Update();
	virtual void Render();
protected:
	Vector2 _pos;
	Vector2 _size;
	Game& _game;
	ModeBase& _mode;
	bool _visible;
};
