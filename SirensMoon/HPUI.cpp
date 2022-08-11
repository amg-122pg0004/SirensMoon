#include "HPUI.h"
#include "ModeBase.h"
#include "Player.h"

HPUI::HPUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size, int windowno)
	:UIBase(game,mode,pos,size),_playerNo{windowno}
{
	_pos = pos;
	_size = size;
	_player_HP.resize(2);
	_cg["high"] = ImageServer::LoadGraph("resource/UI/HP/high.png");
	_cg["middle"] = ImageServer::LoadGraph("resource/UI/HP/middle.png");
	_cg["low"] = ImageServer::LoadGraph("resource/UI/HP/low.png");
	_cg["null"] = -1;
}

void HPUI::Update(){
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if(_playerNo==0){
			if (actor->GetType() == Actor::Type::PlayerA) {
				auto player = dynamic_cast<Player&>(*actor);
				SetHPstring(player.GetHP());
			}
		}
		else {
			if (actor->GetType() == Actor::Type::PlayerB) {
				auto player = dynamic_cast<Player&>(*actor);
				SetHPstring(player.GetHP());
			}
		}
	}

}

void HPUI::Render() {
	DrawGraph(_pos.x,_pos.y, _cg[_player_HP], 1);
}

void HPUI::SetHPstring(int hp) {

	switch (hp) {
	case 1:
		_player_HP = "low";
		break;
	case 2:
		_player_HP = "middle";
		break;
	case 3:
		_player_HP = "high";
		break;
	default:
		_player_HP = "null";
		break;
	}
}
