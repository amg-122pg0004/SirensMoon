#include "FX_AfterBurner.h"
#include "Easing.h"
#include "BossMissile.h"

FX_AfterBurner::FX_AfterBurner(Game& game, ModeGame& mode, const Vector2& pos, int startTime, BossMissile& owner)
	:Effect(game, mode, pos, startTime),_owner{owner}
{
	_cg.resize(41);
	ImageServer::LoadDivGraph("resource/Effect/AfterBurner.png", 41, 4, 11, 90, 90, _cg.data());
	_zoom = 1.0;
	_lifeTime = 41;
	_blendMode = DX_BLENDMODE_ALPHA;
	_loop = true;
}
void FX_AfterBurner::Update() {
	if (_owner.IsDead()) {
		_dead = true;
	}
	auto pos = _owner.GetPosition();
	_angle = _owner.GetAngle();
	Vector2 fix = { cos(_angle),sin(_angle) };
	fix *= -130;
	_pos = pos + fix;
	_angle -= Math::ToRadians(90);
	Effect::Update();
}
void FX_AfterBurner::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);

}