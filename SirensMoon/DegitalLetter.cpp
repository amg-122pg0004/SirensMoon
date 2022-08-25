#include "DegitalLetter.h"
#include "ModeGame.h"
#include "MessageWindow.h"

DegitalLetter::DegitalLetter(Game& game, ModeGame& mode, ObjectDataStructs::DegitalLetterData data)
	:Gimmick(game,mode,data.ID)
{
	_pos = data.pos;
	_size = { 60,60 };
	_message = data.message;
	Vector2 access= { 10,10 };
	_collision.min = data.pos;
	_collision.max = data.pos+_size;
	_accessArea.min = data.pos- access;
	_accessArea.max = data.pos+_size+ access;
	_cg = ImageServer::LoadGraph("resource/Gimmick/degitalletter.png");
}

void DegitalLetter::Update(){
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
		_cg, 0);
}

void DegitalLetter::Debug(Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2 (window_pos, camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);
}
