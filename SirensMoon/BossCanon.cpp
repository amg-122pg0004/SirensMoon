#include "bossCanon.h"
#include "ModeGame.h"
#include "Player.h"

BossCanon::BossCanon(Game& game, ModeGame& mode, Vector2 pos)
	:Actor{ game,mode }, _speed{ 40 }, _lifetime{ 120 }
{
	_cg = ImageServer::LoadGraph("resource/Boss/canon.png");
	_pos = pos;
	_size = { 630,630 };
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

void BossCanon::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 0);
}
