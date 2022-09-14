#include "LaserLight.h"
#include "PlayerA.h"
#include <math.h>

LaserLight::LaserLight(Game& game, ModeGame& mode, Actor& owner)
: LightBase{ game,mode,owner }
{	_cg = ImageServer::LoadGraph("resource/Light/Light_2.png");
int x, y;
GetGraphSize(_cg, &x, &y);
_centerPos = { static_cast<double>(x / 2),static_cast<double>(y) };
_pos = _owner.GetPosition() + _owner.GetSize() / 2;
auto player = dynamic_cast<Player&>(_owner);
_angle = player.GetInputAngle() + Math::ToRadians(90);

}

void LaserLight::Update() {
	auto player = dynamic_cast<Player&>(_owner);
	_pos = _owner.GetPosition() + _owner.GetSize() / 2;
	_angle = player.GetInputAngle() + Math::ToRadians(90);

	switch (player.GetGrDirection()) {
	case Player::PlayerDirection::Up:
		_pos += {5, -40};
		break;
	case Player::PlayerDirection::Down:
		_pos += {-8, 25};
		break;
	case Player::PlayerDirection::Right:
		_pos += {40, -2};
		break;
	case Player::PlayerDirection::Left:
		_pos += {-50, -12};
		break;
	}

	if (dynamic_cast<PlayerA&>(_owner).GetCharge() == 0) {
		_dead = true;
	}
}