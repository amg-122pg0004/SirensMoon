#include "FX_MissileShoot.h"
#include "Easing.h"

FX_MissileShoot::FX_MissileShoot(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(148);
	ImageServer::LoadDivGraph("resource/Effect/MissileShoot.png", 148, 7, 12, 220, 540, _cg.data());
	_zoom = 1.0;
	_lifeTime = 148;
	_blendMode = DX_BLENDMODE_NOBLEND;
}

void FX_MissileShoot::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}