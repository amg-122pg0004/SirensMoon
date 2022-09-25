#include "FX_HeadButt.h"
#include "Easing.h"

FX_HeadButt::FX_HeadButt(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{

	_cg.resize(26);
	ImageServer::LoadDivGraph("resource/Effect/headbutt.png", 26, 9, 3, 128, 128, _cg.data());

	_zoom = 4;
	_lifeTime = 30 * 1;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_HeadButt::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime));
}