#include "DegitalLetter.h"
#include "ModeGame.h"
#include "MessageWindow.h"

DegitalLetter::DegitalLetter(Game& game, ModeGame& mode, ObjectDataStructs::DegitalLetterData data)
	:Gimmick(game,mode,data.ID)
{
	_pos = data.pos;
	_size = { 60,60 };
	Vector2 access= { 10,10 };
	_collision.min = data.pos;
	_collision.max = data.pos+_size;
	_accessArea.min = data.pos- access;
	_accessArea.max = data.pos+_size+ access;
	_cg = ImageServer::LoadGraph("resource/UI/DegitalLetter/degitalletter.png");
}

void DegitalLetter::Update(){
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
				for (auto&& actor:_mode.GetSplitWindow()[0]->GetUIServer()) {
					if (actor->GetType() == UIBase::Type::MessageWindow) {
						dynamic_cast<MessageWindow&>(*actor).SetMessage(_message);
					}
				}
			}
			else {
				for (auto&& actor : _mode.GetSplitWindow()[0]->GetUIServer()) {
					if (actor->GetType() == UIBase::Type::MessageWindow) {
						std::string str;
						dynamic_cast<MessageWindow&>(*actor).SetMessage(str);
					}
				}
			}
		}
		if (actor->GetType() == Type::PlayerB) {
			if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {
				for (auto&& actor : _mode.GetSplitWindow()[1]->GetUIServer()) {
					if (actor->GetType() == UIBase::Type::MessageWindow) {
						dynamic_cast<MessageWindow&>(*actor).SetMessage(_message);
					}
				}
			}
			else {
				for (auto&& actor : _mode.GetSplitWindow()[0]->GetUIServer()) {
					if (actor->GetType() == UIBase::Type::MessageWindow) {
						std::string str;
						dynamic_cast<MessageWindow&>(*actor).SetMessage(str);
					}
				}
			}
		}
	}
}
void DegitalLetter::StandardRender(int stagenum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x - _size.x/2),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y - _size.y / 2),
		_cg, 0);
}

void DegitalLetter::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2 (stageNum, window_pos, camera_pos);
	_accessArea.Draw2(stageNum, window_pos, camera_pos);
}
