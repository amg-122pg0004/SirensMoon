#include "UIBase.h"

class Game;
class ModeBase;

UIBase::UIBase(Game& game, ModeBase& mode, Vector2 pos, Vector2 size) 
	:_game{ game }, _mode{ mode }, _pos{ pos }, _size{ size }
{

}

UIBase::~UIBase() {

}

void UIBase::Update() {

}

void UIBase::Render(){

}