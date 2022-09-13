#include "FX_ScreenSmoke.h"
#include "Easing.h"


FX_ScreenSmoke::FX_ScreenSmoke(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(117);
	ImageServer::LoadDivGraph("resource/Effect/ScreenSmoke.png", 117, 5, 24, 256, 256, _cg.data());

	_zoom = 1.1;
	_lifeTime = 117;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_ScreenSmoke::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}