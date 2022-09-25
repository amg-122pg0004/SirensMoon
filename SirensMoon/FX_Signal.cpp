#include "FX_Signal.h"
#include "Easing.h"

FX_Signal::FX_Signal(Game& game, ModeGame& mode, const Vector2& pos, int startTime, bool longSignal)
	:Effect(game, mode, pos, startTime), _moveLength{ 80 }
{
	_cg.resize(1);
	if (longSignal) {
		_cg[0] = ImageServer::LoadGraph("resource/Effect/SignalLong.png");
	}
	else {
		_cg[0] = ImageServer::LoadGraph("resource/Effect/Signal.png");
	}

	_zoom = 1.0;
	_lifeTime = 90;
	_blendMode = DX_BLENDMODE_ALPHA;
	_startPos = _pos;
	_renderPriority = 0;
}
void FX_Signal::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(linear(elapsed, 0, 0, _lifeTime));
	_pos.y = _startPos.y - linear(elapsed, 0, _moveLength, _lifeTime);
}