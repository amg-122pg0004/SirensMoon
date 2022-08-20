/*****************************************************************//**
 * \file   MiniMap.cpp
 * \brief  ミニマップを表示するUIです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "MiniMap.h"
#include "ModeGame.h"
#include "DisplayArea.h"
#include "Boss.h"

MiniMap::MiniMap(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size },_blind2Flag{false}
{
	_cg_map = ImageServer::LoadGraph("resource/UI/map_frame.png");
	_visible = false;
	_inputManager = _game.GetInputManager();

	_movieHandle = ImageServer::LoadGraph("resource/Server/noise.mp4");

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

	if (_inputManager->CheckInput("BLIND2", 't', 0) || _inputManager->CheckInput("BLIND2", 't', 1)) {
		_blind2Flag = !_blind2Flag;
	}

	if (dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetLightUp() != 255) {
		if (_prelightUp == 255 ) {
			_noiseFlag = true;
			SeekMovieToGraph(_movieHandle,0);
			PlayMovieToGraph(_movieHandle);
		}
	}
	if (_noiseFlag) {
		if (GetMovieStateToGraph(_movieHandle) != 1) {
			_noiseFlag = false;
		}
	}


	_prelightUp = dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[1]->GetLightUp();
}

void MiniMap::Render() {

	if (_visible) {
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x),static_cast<int>(_pos.y + _size.y), _cg_map, 0);

		Vector2 pos = { 1280,103 };
		Vector2 pos2 = { 0,0 };

		dynamic_cast<ModeGame&>(_mode).GetMapChips()->ReconRender(0, pos, pos2);
		
		//float scale = 410.0f / 3240.0f * 0.97f;
		float scale = 410.0f / 4320.0f * 0.97f;
		for (auto&& actor : _mode.GetObjects()) {
			if (!_blind2Flag) {
				if (actor->GetType() == Actor::Type::PlayerA) {
					Player& player = dynamic_cast<Player&>(*actor);
					if (player.GetPlayerNum() == 0) {
						DrawBox(static_cast<int>(actor->GetPosition().x * scale + pos.x),
							static_cast<int>(actor->GetPosition().y * scale + pos.y),
							static_cast<int>(actor->GetPosition().x * scale + pos.x) + 5,
							static_cast<int>(actor->GetPosition().y * scale + pos.y) + 5,
							GetColor(255, 0, 0), 1);
					}
				}
				if (actor->GetType() == Actor::Type::PlayerB) {
					Player& player = dynamic_cast<Player&>(*actor);
					if (player.GetPlayerNum() == 1) {
						DrawBox(static_cast<int>(actor->GetPosition().x * scale + pos.x),
							static_cast<int>(actor->GetPosition().y * scale + pos.y),
							static_cast<int>(actor->GetPosition().x * scale + pos.x) + 5,
							static_cast<int>(actor->GetPosition().y * scale + pos.y) + 5,
							GetColor(0, 0, 255), 1);
					}
				}
			}
			
			if (actor->GetType() == Actor::Type::Enemy) {
				DrawBox(static_cast<int>(actor->GetPosition().x * scale + pos.x),
					static_cast<int>(actor->GetPosition().y * scale + pos.y),
					static_cast<int>(actor->GetPosition().x * scale + pos.x) + 5,
					static_cast<int>(actor->GetPosition().y * scale + pos.y) + 5,
					GetColor(255, 0, 255), 1);
			}
			if (actor->GetType() == Actor::Type::Boss) {
				auto size = actor->GetSize();
				auto bossscale = dynamic_cast<Boss&>(*actor).GetScale();
				DrawBox(static_cast<int>((actor->GetPosition().x - size.x * bossscale/2)  * scale + pos.x),
					static_cast<int>((actor->GetPosition().y - size.y * bossscale / 2) * scale + pos.y),
					static_cast<int>((actor->GetPosition().x + size.x * bossscale / 2) * scale + pos.x),
					static_cast<int>((actor->GetPosition().y + size.y * bossscale / 2)  * scale + pos.y),
					GetColor(255, 0, 255), 1);
			}
			if (actor->GetType() == Actor::Type::Server) {
				DrawBox(static_cast<int>(actor->GetPosition().x * scale + pos.x),
					static_cast<int>(actor->GetPosition().y * scale + pos.y),
					static_cast<int>(actor->GetPosition().x * scale + pos.x) + 5,
					static_cast<int>(actor->GetPosition().y * scale + pos.y) + 5,
					GetColor(255, 255, 0), 1);
			}
			if (actor->GetType() == Actor::Type::DisplayArea) {
				auto area=dynamic_cast<DisplayArea&>(*actor).GetDisplayArea();
				DrawBox(static_cast<int>(area.min.x * scale + pos.x),
					static_cast<int>(area.min.y * scale + pos.y),
					static_cast<int>(area.max.x * scale + pos.x),
					static_cast<int>(area.max.y * scale + pos.y),
					GetColor(150, 30, 30), 1);
			}
		}
		if (_noiseFlag) {
			DrawExtendGraph(1280, 103,1280+350,103+400, _movieHandle, 0);
		}
	}
}
