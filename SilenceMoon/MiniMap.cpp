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
#include <sstream>

class SplitWindow;

MiniMap::MiniMap(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size }, _boss{ false }, _open{ false }, _animNo{0}
{
	_visiblePos = _pos;
	_pos.y -= _size.y;
	_hidePos = _pos;
	_font = _game.GetFont22();
	_cg_base = ImageServer::LoadGraph("resource/UI/Minimap/map_base.png");
	_cg_earth.resize(3);
	ImageServer::LoadDivGraph("resource/UI/Minimap/Earth.png", 3, 3, 1, 87, 149, _cg_earth.data());
	_cg_cross = ImageServer::LoadGraph("resource/UI/Minimap/map_cross.png");
	_cg_bar = ImageServer::LoadGraph("resource/UI/Minimap/map_bar2.png");
	_cg_line = ImageServer::LoadGraph("resource/UI/Minimap/map_line.png");
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
		StartJoypadVibration(DX_INPUT_PAD2, 50, 50, -1);
		if (!_visible) {
			PlaySoundMem(SoundServer::Find("MiniMapOpen"), DX_PLAYTYPE_BACK);
			PlaySoundMem(SoundServer::Find("MiniMapLooking"), DX_PLAYTYPE_LOOP);
			_visible = true;
			_open = true;
		}
	}
	else {
		if (_open) {
			StopSoundMem(SoundServer::Find("MiniMapLooking"));
			PlaySoundMem(SoundServer::Find("MiniMapClose"), DX_PLAYTYPE_BACK);
			_open = false;
		}
	}
	if (_open) {
		_pos.y += 80;
		if (_pos.y > _visiblePos.y) {
			_pos.y = _visiblePos.y;
		}
	}
	else {
		_pos.y -= 100;
		if (_pos.y < _hidePos.y) {
			_pos.y = _hidePos.y;
			_visible = false;
		}
	}

	if (_noiseFlag) {
		if (GetMovieStateToGraph(_movieHandle) != 1) {
			_noiseFlag = false;

		}
	}
	if (_game.GetFrameCount() % 100 == 0) {
		++_animNo;
		if (_animNo > 2) {
			_animNo = 0;
		}
	}
}

void MiniMap::Render() {
	if (!_visible) {
		return;
	}
	DrawBox(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
		static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y),
		GetColor(28,28,73),true);
	Vector2 pos = { _pos.x + 215.0,_pos.y + 95.0 };
	DrawBox(static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(pos.x + 350), static_cast<int>(pos.y + 410),
		GetColor(0, 0, 0), true);
		
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),_cg_base, 1);
	Vector2 earth_pos = { _pos.x + 92.0,_pos.y + 360.0 };
	DrawGraph(static_cast<int>(earth_pos.x), static_cast<int>(earth_pos.y),_cg_earth[_animNo], 1);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg_cross, 1);
	int cg_bar{-1};
	cg_bar = DerivationGraph(_game.GetFrameCount()/10%825, 0, 413, 47, _cg_bar);
	DrawGraph(static_cast<int>(_pos.x+190), static_cast<int>(_pos.y+515), cg_bar, 1);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg_line, 1);

	DrawExtendGraph(static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(pos.x + 350), static_cast<int>(pos.y + 410), _cg_grid, 1);
	SetDrawArea(static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(pos.x + 350), static_cast<int>(pos.y + 410));

	Vector2 pos2 = { 0,0 };
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
			DrawBox(static_cast<int>((actor->GetPosition().x - size.x * bossscale) * scalex + pos.x),
				static_cast<int>((actor->GetPosition().y - size.y * bossscale) * scaley + pos.y),
				static_cast<int>((actor->GetPosition().x + size.x * bossscale) * scalex + pos.x),
				static_cast<int>((actor->GetPosition().y + size.y * bossscale) * scaley + pos.y),
				GetColor(255, 0, 255), 1);
		}
		if (actor->GetType() == Actor::Type::Server) {
			DrawBox(static_cast<int>(actor->GetPosition().x * scalex + pos.x),
				static_cast<int>(actor->GetPosition().y * scaley + pos.y),
				static_cast<int>(actor->GetPosition().x * scalex + pos.x) + 5,
				static_cast<int>(actor->GetPosition().y * scaley + pos.y) + 5,
				GetColor(255, 255, 0), 1);
			std::stringstream ss;
			ss << "目的地";
			DrawStringToHandle(static_cast<int>(actor->GetPosition().x * scalex + pos.x-30)
				, static_cast<int>(actor->GetPosition().y * scaley + pos.y-26)
				,ss.str().c_str(),GetColor(255,255,0), _font);
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

	SetDrawArea(0, 0, screen_W, screen_H);
}

void MiniMap::SetBossFlag() {
	_boss = true;
}

void MiniMap::TargetSpawnEvent() {
	_noiseFlag = true;
	SeekMovieToGraph(_movieHandle, 0);
	PlayMovieToGraph(_movieHandle);
}
