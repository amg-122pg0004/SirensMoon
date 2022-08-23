#include "FX_Chargenow.h"
#include "Easing.h"
#include "Player.h"

FX_Chargenow::FX_Chargenow(Game& game, ModeGame& mode, const Vector2& pos, int startTime, Player& owner)
	:Effect(game, mode, pos, startTime), _owner{ owner }
{
	_cg.resize(60);
	ImageServer::LoadDivGraph("resource/Effect/chargenow.png", 60, 8, 8, 512, 512, _cg.data());

	_zoom = 0.3;
	_lifeTime = 60 * 2.0;
	_blendMode = DX_BLENDMODE_ALPHA;
	_loop = true;

	switch (_owner.GetGrDirection()) {
	case Player::PlayerDirection::Up:
		_pos += {22, -15};
		break;
	case Player::PlayerDirection::Down:
		_pos += {5, 45};
		break;
	case Player::PlayerDirection::Right:
		_pos += {60, 10};
		break;
	case Player::PlayerDirection::Left:
		_pos += {-30, 3};
		break;
	}
}

void FX_Chargenow::Update() {
	_loop = true;
	_pos = _owner.GetPosition();
	switch (_owner.GetGrDirection()) {
	case Player::PlayerDirection::Up:
		_pos += {18, -15};
		break;
	case Player::PlayerDirection::Down:
		_pos += {5, 45};
		break;
	case Player::PlayerDirection::Right:
		_pos += {60, 10};
		break;
	case Player::PlayerDirection::Left:
		_pos += {-30, 0};
		break;
	}
	Effect::Update();
	_renderPriority = _pos.y + 60;
	if (_owner.GetCharge() == 0) {
		_dead = true;
	}
}

void FX_Chargenow::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}