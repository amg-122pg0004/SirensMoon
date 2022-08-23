#include "DegitalLetter.h"
#include "ModeGame.h"

DegitalLetter::DegitalLetter(Game& game, ModeGame& mode, ObjectDataStructs::DegitalLetterData data)
	:Gimmick(game,mode,data.ID)
{
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
				
			}
			else {

			}
		}
		if (actor->GetType() == Type::PlayerB) {
			if (Intersect(_accessArea, dynamic_cast<Player&>(*actor).GetCollision())) {

			}
			else {

			}
		}
	}
}

void DegitalLetter::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2 (stageNum, window_pos, camera_pos);
	_accessArea.Draw2(stageNum, window_pos, camera_pos);
}
