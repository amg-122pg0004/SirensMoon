#include "DegitalLetter.h"
#include "ModeGame.h"
#include "MessageWindow.h"

DegitalLetter::DegitalLetter(Game& game, ModeGame& mode, ObjectDataStructs::DegitalLetterData data)
	:Gimmick(game,mode,data.ID),_animNo{0}
{
	_pos = data.pos;
	_size = { 60,60 };
	_message = data.message;
	Vector2 access= { 10,10 };
	_collision.min = {-1,-1};
	_collision.max = {-1,-1};
	_accessArea.min = data.pos- access;
	_accessArea.max = data.pos+_size+ access;
	_cg.resize(39);
	ImageServer::LoadDivGraph("resource/Gimmick/digitaletter.png",39,3,13,60,60,_cg.data());
}

void DegitalLetter::Update(){
	if (_game.GetFrameCount() % 2 == 0) {
		++_animNo;
	}
	
	if (_animNo >= _cg.size()) {
		_animNo = 0;
	}
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
				_accessible1 = true;
				for (auto&& actor:_mode.GetSplitWindow()[0]->GetUIServer()) {
					if (actor->GetType() == UIBase::Type::MessageWindow) {
						dynamic_cast<MessageWindow&>(*actor).SetMessage(_message);
					}
				}
			}
			else {
				_accessible1 = false;
			}
		}
		if (actor->GetType() == Type::PlayerB) {
			if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
				_accessible2 = true;
				for (auto&& actor : _mode.GetSplitWindow()[1]->GetUIServer()) {
					if (actor->GetType() == UIBase::Type::MessageWindow) {
						dynamic_cast<MessageWindow&>(*actor).SetMessage(_message);
					}
				}
			}
			else {
				_accessible2 = false;
			}
		}
	}
}
void DegitalLetter::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
		_cg[_animNo], 1);
}

void DegitalLetter::Debug(Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2 (window_pos, camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);
}
