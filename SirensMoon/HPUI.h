#pragma once
#include "UIBase.h"
#include <unordered_map>

class Game;
class ModeGame;

class HPUI :public UIBase{
public:
	HPUI(Game&, ModeBase&, Vector2 pos, Vector2 size,int windowno);
	
	Type GetType()override { return Type::HP; }

	void Update();
	void Render();

private:
	void SetHPstring(int hp);
	std::unordered_map<std::string,int> _cg;

	std::string _player_HP;
	int _playerNo;
};
