#include "FX_Chargein.h"
#include "Easing.h"
#include "PlayerA.h"


FX_Chargein::FX_Chargein(Game& game, ModeGame& mode, const Vector2& pos, int startTime, Player& owner)
	:Effect(game, mode, pos, startTime),_owner{owner}
{

	_cg.resize(119);
	ImageServer::LoadDivGraph("resource/Effect/chargein.png", 119, 8, 15, 64, 64, _cg.data());

	_zoom = 2.0;
	_lifeTime = 105;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_Chargein::Update() {

	_pos = _owner.GetPosition();
	switch (_owner.GetGrDirection()) {
	case Player::PlayerDirection::Up:
		_pos += {20, -15};
		break;
	case Player::PlayerDirection::Down:
		_pos += {5, 45};
		break;
	case Player::PlayerDirection::Right:
		_pos += {60, 13};
		break;
	case Player::PlayerDirection::Left:
		_pos += {-30, 6};
		break;

	}
	Effect::Update();
	_renderPriority = static_cast<int>(_pos.y + 60);
	if (dynamic_cast<PlayerA&>(_owner).GetCharge() == 0) {
		_dead = true;
	}
}

void FX_Chargein::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}