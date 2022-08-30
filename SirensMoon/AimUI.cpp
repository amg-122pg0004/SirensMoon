#include "AimUI.h"
#include "Game.h"

AimUI::AimUI(Game& game, ModeBase& mode,Vector2 pos,Vector2 size)
	:UIBase(game,mode,pos,size)
{
	
	_cg = ImageServer::LoadGraph("resource/UI/AimUI/frame2.png");
	_cg_cursor = ImageServer::LoadGraph("resource/UI/AimUI/cursor.png");
	_pos_cursor = {_pos.x+930/2,_pos.y+1080/2};
	_visible = true;
}

void AimUI::Update() {
	Vector2 dir =_game.GetInputManager()->CheckAnalogInput(0)/1000;
	dir.Normalize();
	_pos_cursor += (dir * _speed);
	if (_pos_cursor.x < 0) {
		_pos_cursor.x = 0;
	}
	if (_pos_cursor.x > splitscreen_W) {
		_pos_cursor.x = splitscreen_W;
	}
	if (_pos_cursor.y < 0) {
		_pos_cursor.y = 0;
	}
	if (_pos_cursor.y > screen_H) {
		_pos_cursor.y = screen_H;
	}
}

void AimUI::Render(){
	if (_visible) {
		DrawRotaGraph(_pos_cursor.x,_pos_cursor.y,1.0,1.0,_cg_cursor,0);
		DrawGraph(0, 0, _cg, 1);
	}
}
