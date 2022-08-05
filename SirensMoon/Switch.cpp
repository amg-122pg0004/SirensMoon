#include "Switch.h"

Switch::Switch(Game& game, ModeGame& mode)
	:Actor(game,mode)
{
	_linkGimmiks[0] = nullptr;
}

void Switch::Update(){

}

void Switch::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos){

}
