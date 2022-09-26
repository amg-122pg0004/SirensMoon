/*****************************************************************//**
 * \file   BossCanon.h
 * \brief  É{ÉXÇ™åÇÇ¬ëÂñCÇÃã îªíË
 *
 * \author ìyãèè´ëæòY
 * \date   September 2022
 *********************************************************************/
#include "bossCanon.h"
#include "ModeGame.h"
#include "Player.h"
#include "FX_BossFire.h"

BossCanon::BossCanon(Game& game, ModeGame& mode, Vector2 pos)
	:Actor{ game,mode }, _speed{ 40 }, _lifetime{ 120 }
{
	//_cg = ImageServer::LoadGraph("resource/Boss/canon.png");
	_pos = pos;
	_size = { 630,630 };
	Vector2 posfix = { _pos.x+_size.x/2,_pos.y+500 };
	_mode.GetActorServer().Add(std::make_unique<FX_BossFire>(_game, _mode, posfix, _game.GetFrameCount()));
	StartJoypadVibration(DX_INPUT_PAD1, 500, 150, -1);
	StartJoypadVibration(DX_INPUT_PAD2, 500, 150, -1);
}

BossCanon::~BossCanon() {

}

void BossCanon::Update() {
	_pos.y = _pos.y + _speed;
	UpdateCollision();

	--_lifetime;

	if (_lifetime < 0) {

		Dead();
	}
}

void BossCanon::UpdateCollision() {
	_collision.min = _pos;
	_collision.max = _pos + _size;
}

void BossCanon::StandardRender( Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 0);
}
