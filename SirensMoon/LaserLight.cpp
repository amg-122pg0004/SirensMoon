#include "LaserLight.h"
#include "Player.h"
#include <math.h>

LaserLight::LaserLight(Game& game, ModeGame& mode, Actor& owner)
: LightBase{ game,mode,owner }
{	_cg = ImageServer::LoadGraph("resource/Light/Light_2.png");
int x, y;
GetGraphSize(_cg, &x, &y);
_centerPos = { static_cast<double>(x / 2),static_cast<double>(y) };
_pos = _owner.GetPosition() + _owner.GetSize() / 2;
auto player = dynamic_cast<Player&>(_owner);
_angle = atan2(player.GetDirection().y, player.GetDirection().x) + (3.14 / 2.0);

}

void LaserLight::Update() {
	auto player = dynamic_cast<Player&>(_owner);
	_pos = _owner.GetPosition() + _owner.GetSize() / 2;
	_angle = atan2(player.GetDirection().y, player.GetDirection().x) + (3.14 / 2.0);


	if (player.GetCharge() == 0) {
		_dead = true;
	}
}
