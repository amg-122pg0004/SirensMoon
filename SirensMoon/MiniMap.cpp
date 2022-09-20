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
#include "Enemy.h"
#include "Boss.h"
#include "Gimmick.h"

MiniMap::MiniMap(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size },_boss{false}
{
	_cg_map = ImageServer::LoadGraph("resource/UI/map_frame.png");
	_cg_grid = ImageServer::LoadGraph("resource/UI/Minimap/grid.png");
	_visible = false;
	_inputManager = _game.GetInputManager();

	_movieHandle = ImageServer::LoadGraph("resource/Server/noise.mp4");
	_UIPriority = 1;
}

MiniMap::~MiniMap() {

}

void MiniMap::Update() {

	if (_inputManager->CheckInput("ACTION", 'h', 1)) {
		if (!_visible) {
			PlaySoundMem(SoundServer::Find("MiniMapOpen"), DX_PLAYTYPE_BACK);
			_visible = true;
			StartJoypadVibration(DX_INPUT_PAD2, 50, 50, -1);
		}
	}
	else {
		if (_visible) {
			StopSoundMem(SoundServer::Find("MiniMapClose"));
			PlaySoundMem(SoundServer::Find("MiniMapClose"), DX_PLAYTYPE_BACK);
			_visible = false;
		}
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
	if (!_visible) {
		return;
	}

	DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
		static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), _cg_map, 0);

	Vector2 pos = { 1280,95 };
	Vector2 pos2 = { 0,0 };

	DrawExtendGraph(static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(pos.x + 350), static_cast<int>(pos.y + 410), _cg_grid, 1);
	SetDrawArea(static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(pos.x + 350), static_cast<int>(pos.y + 410));

	dynamic_cast<ModeGame&>(_mode).GetMapChips()->MiniMapRender(0, pos, pos2, _boss);
	float scalex{ 1 }, scaley{ 1 };
	if (_boss) {
		scalex = static_cast<float>(345.0 * 4.0 / (30 * 125));
		scaley = static_cast<float>(400.0 * 4.0 / (30 * 144));
	}
	else {
		scalex = static_cast<float>(345.0 / (30 * 125));
		scaley = static_cast<float>(400.0 / (30 * 144));
	}

	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::Enemy) {
			auto eyepos = dynamic_cast<Enemy&>(*actor).GetSightPosition();
			auto col_pos = (actor->GetCollision().min + actor->GetCollision().max) / 2;
			DrawBox(static_cast<int>(col_pos.x * scalex + pos.x) - 2,
				static_cast<int>(col_pos.y * scaley + pos.y) - 2,
				static_cast<int>(col_pos.x * scalex + pos.x) + 3,
				static_cast<int>(col_pos.y * scaley + pos.y) + 3,
				GetColor(255, 0, 255), 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

			DrawTriangleAA(static_cast<float>(eyepos.pos1.x * scalex + pos.x),
				static_cast<float>(eyepos.pos1.y * scaley + pos.y),
				static_cast<float>(eyepos.pos2.x * scalex + pos.x),
				static_cast<float>(eyepos.pos2.y * scaley + pos.y),
				static_cast<float>(eyepos.pos3.x * scalex + pos.x),
				static_cast<float>(eyepos.pos3.y * scaley + pos.y),
				GetColor(255, 0, 255), 1);
			DrawTriangleAA(static_cast<float>(eyepos.pos2.x * scalex + pos.x),
				static_cast<float>(eyepos.pos2.y * scaley + pos.y),
				static_cast<float>(eyepos.pos3.x * scalex + pos.x),
				static_cast<float>(eyepos.pos3.y * scaley + pos.y),
				static_cast<float>(eyepos.pos4.x * scalex + pos.x),
				static_cast<float>(eyepos.pos4.y * scaley + pos.y),
				GetColor(255, 0, 255), 1);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		if (actor->GetType() == Actor::Type::Boss) {
			auto size = actor->GetSize();
			auto bossscale = dynamic_cast<Boss&>(*actor).GetMapScale();
			DrawBox(static_cast<int>((actor->GetPosition().x - size.x * bossscale ) * scalex + pos.x),
				static_cast<int>((actor->GetPosition().y - size.y * bossscale ) * scaley + pos.y),
				static_cast<int>((actor->GetPosition().x + size.x * bossscale ) * scalex + pos.x),
				static_cast<int>((actor->GetPosition().y + size.y * bossscale ) * scaley + pos.y),
				GetColor(255, 0, 255), 1);
		}
		if (actor->GetType() == Actor::Type::Server) {
			DrawBox(static_cast<int>(actor->GetPosition().x * scalex + pos.x),
				static_cast<int>(actor->GetPosition().y * scaley + pos.y),
				static_cast<int>(actor->GetPosition().x * scalex + pos.x) + 5,
				static_cast<int>(actor->GetPosition().y * scaley + pos.y) + 5,
				GetColor(255, 255, 0), 1);
		}
		if (actor->GetType() == Actor::Type::DisplayArea) {
			auto area = dynamic_cast<DisplayArea&>(*actor).GetDisplayArea();
			DrawBox(static_cast<int>(area.min.x * scalex + pos.x),
				static_cast<int>(area.min.y * scaley + pos.y),
				static_cast<int>(area.max.x * scalex + pos.x),
				static_cast<int>(area.max.y * scaley + pos.y),
				GetColor(150, 30, 30), 1);
		}
		if (actor->GetType() == Actor::Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigServer) {
				DrawBox(static_cast<int>(actor->GetPosition().x * scalex + pos.x),
					static_cast<int>(actor->GetPosition().y * scaley + pos.y),
					static_cast<int>(actor->GetPosition().x * scalex + pos.x) + 10,
					static_cast<int>(actor->GetPosition().y * scaley + pos.y) + 10,
					GetColor(255, 255, 0), 1);
			}
		}
		if (actor->GetType() == Actor::Type::PlayerA) {
			DrawBox(static_cast<int>(actor->GetPosition().x * scalex + pos.x),
				static_cast<int>(actor->GetPosition().y * scaley + pos.y),
				static_cast<int>(actor->GetPosition().x * scalex + pos.x) + 5,
				static_cast<int>(actor->GetPosition().y * scaley + pos.y) + 5,
				GetColor(255, 0, 0), 1);
		}
		if (actor->GetType() == Actor::Type::PlayerB) {
			DrawBox(static_cast<int>(actor->GetPosition().x * scalex + pos.x),
				static_cast<int>(actor->GetPosition().y * scaley + pos.y),
				static_cast<int>(actor->GetPosition().x * scalex + pos.x) + 5,
				static_cast<int>(actor->GetPosition().y * scaley + pos.y) + 5,
				GetColor(0, 0, 255), 1);
		}
	}
	if (_noiseFlag) {
		DrawExtendGraph(1280, 103, 1280 + 350, 103 + 400, _movieHandle, 0);
	}
	auto&& window = dynamic_cast<ModeGame&>(_mode).GetSplitWindow();
	/*
	SetDrawArea(static_cast<int>(window[0]->GetWindowPos().x),
		static_cast<int>(window[0]->GetWindowPos().y),
		static_cast<int>(window[0]->GetWindowPos().x + splitscreen_W),
		static_cast<int>(window[0]->GetWindowPos().y + screen_H));
		*/
	SetDrawArea(0, 0, screen_W, screen_H);
}

void MiniMap::SetBossFlag(){
	_boss = true;
}
