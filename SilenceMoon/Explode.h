#pragma once
#include "Actor.h"

class Game;
class ModeGame;

class Explode :public Actor {
public:
	Explode(Game& game,ModeGame& mode,Vector2 pos);
	void Update();
	void StandardRender(Vector2 window_pos, Vector2 camera_pos) override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Explode; }

private:
	int _lifetime;
	int _delay;
};

class Explode2 :public Actor {
public:
	Explode2(Game& game, ModeGame& mode, Vector2 pos);
	void Update();
	void StandardRender(Vector2 window_pos, Vector2 camera_pos) override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Explode; }

private:
	int _lifetime;
	int _delay;
};

class Explode3 :public Actor {
public:
	Explode3(Game& game, ModeGame& mode, Vector2 pos);
	void Update();
	void StandardRender(Vector2 window_pos, Vector2 camera_pos) override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Explode; }

private:
	int _lifetime;
	int _delay;
};