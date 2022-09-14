#include "FX_BulletHit.h"
#include "Easing.h"

FX_BulletHit::FX_BulletHit(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_zoom = 2.0;
	_lifeTime = 88;
	_blendMode = DX_BLENDMODE_ALPHA;
	_cg.resize(88);
}

void FX_BulletHit::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);

}

FX_BulletHitRed::FX_BulletHitRed(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:FX_BulletHit(game, mode, pos, startTime)
{
	ImageServer::LoadDivGraph("resource/Effect/bullethitred.png", 88, 8, 11, 128, 128, _cg.data());
}

FX_BulletHitGreen::FX_BulletHitGreen(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:FX_BulletHit(game, mode, pos, startTime)
{
	ImageServer::LoadDivGraph("resource/Effect/bullethitgreen.png", 88, 8, 11, 128, 128, _cg.data());

}
