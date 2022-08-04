/*****************************************************************//**
 * \file   MiniMap.cpp
 * \brief  ミニマップを表示するUIです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "MiniMap.h"
#include "ImageServer.h"
#include "ModeGame.h"

MiniMap::MiniMap(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }
{
	_cg_map = ImageServer::LoadGraph("resource/UI/map_frame.png");
	_cg_player = ImageServer::LoadGraph("resource/Player/recon.png");
	_cg_enemy = ImageServer::LoadGraph("resource/enemy/recon.png");
	_visible = false;
	_inputManager = _game.GetInputManager();
}

MiniMap::~MiniMap() {

}

void MiniMap::Update() {

	if (_inputManager->CheckInput("ACTION", 'h', 1)) {
		_visible =true;
	}
	else {
		_visible = false;
	}
}

void MiniMap::Render() {

	if (_visible) {
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x),static_cast<int>(_pos.y + _size.y), _cg_map, 0);

		Vector2 pos = { 1290,103 };
		Vector2 pos2 = { 0,0 };

		dynamic_cast<ModeGame&>(_mode).GetMapChips()->ReconRender(0, pos, pos2);
		
		//float scale = 410.0f / 3240.0f * 0.97f;
		float scale = 410.0f / 4320.0f * 0.97f;
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Actor::Type::PlayerA) {
				Player& player = dynamic_cast<Player&>(*actor);
				if (player.GetPlayerNum() == 0) {
					DrawBox(static_cast<int>(actor->GetPosition().x * scale + pos.x),
						static_cast<int>(actor->GetPosition().y * scale + pos.y),
						static_cast<int>(actor->GetPosition().x * scale + pos.x) + 5,
						static_cast<int>(actor->GetPosition().y * scale + pos.y) + 5,
						GetColor(0, 0, 255), 1);
				}
			}
			if (actor->GetType() == Actor::Type::PlayerB) {
				Player& player = dynamic_cast<Player&>(*actor);
				if (player.GetPlayerNum() == 1) {
					DrawBox(static_cast<int>(actor->GetPosition().x * scale + pos.x),
						static_cast<int>(actor->GetPosition().y * scale + pos.y),
						static_cast<int>(actor->GetPosition().x * scale + pos.x) + 5,
						static_cast<int>(actor->GetPosition().y * scale + pos.y) + 5,
						GetColor(255, 0, 0), 1);
				}
			}
			
			if (actor->GetType() == Actor::Type::Enemy) {
				DrawBox(static_cast<int>(actor->GetPosition().x * scale + pos.x),
					static_cast<int>(actor->GetPosition().y * scale + pos.y),
					static_cast<int>(actor->GetPosition().x * scale + pos.x) + 5,
					static_cast<int>(actor->GetPosition().y * scale + pos.y) + 5,
					GetColor(255, 255, 255), 1);
			}

			if (actor->GetType() == Actor::Type::Server) {
				DrawBox(static_cast<int>(actor->GetPosition().x * scale + pos.x),
					static_cast<int>(actor->GetPosition().y * scale + pos.y),
					static_cast<int>(actor->GetPosition().x * scale + pos.x) + 5,
					static_cast<int>(actor->GetPosition().y * scale + pos.y) + 5,
					GetColor(255, 255, 0), 1);
			}
			
		}
	}
}
