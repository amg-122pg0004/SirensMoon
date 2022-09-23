#include "LaserLight.h"
#include "PlayerA.h"
#include "ModeGame.h"
#include "Enemy.h"
#include <math.h>

LaserLight::LaserLight(Game& game, ModeGame& mode, Actor& owner)
	: LightBase{ game,mode,owner }
{
	//_cg = ImageServer::LoadGraph("resource/Light/Light_2.png");
	int x, y;
	GetGraphSize(_cg, &x, &y);
	_centerPos = { static_cast<double>(x / 2),static_cast<double>(y) };
	_pos = _owner.GetPosition() + _owner.GetSize() / 2;
	_extendPoint = _pos;
	auto player = dynamic_cast<Player&>(_owner);
	_angle = player.GetInputAngle() + Math::ToRadians(90);
	_alpha = 180;
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
	auto angle = _angle - Math::ToRadians(90);
	Vector2 extendPoint{ _pos };
	Vector2 stepLength{ cos(angle) * 5 ,sin(angle) * 5 };
	for (int i = 0; i < 1000; ++i) {
		extendPoint += stepLength;
		if (_mode.GetMapChips()->IsHit(extendPoint)) {
			break;
		}
		if (CheckHitEnemy(extendPoint)) {
			break;
		}
	}

	if (angle < Math::ToRadians(0)) {
		extendPoint.y += 30;
	}
	if (angle > Math::ToRadians(90)&& angle < Math::ToRadians(-90)) {
		extendPoint.x += 30;
	}
	_extendPoint = extendPoint;
}

void LaserLight::MaskRender(Vector2 window_pos, Vector2 camera_pos) {
	if (_activate) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawLine(window_pos.x - camera_pos.x + _pos.x,
			window_pos.y - camera_pos.y + _pos.y,
			window_pos.x - camera_pos.x + _extendPoint.x,
			window_pos.y - camera_pos.y + _extendPoint.y,
			GetColor(255, 0, 0), 3);
	}
}

bool LaserLight::CheckHitEnemy(Vector2 extendPoint) {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Enemy) {
			auto col = static_cast<Enemy&>(*actor).GetHitBox();
			if (col.min.x < extendPoint.x && extendPoint.x < col.max.x) {
				if (col.min.y < extendPoint.y && extendPoint.y < col.max.y) {

					return true;
				}
			}
		}
	}
	return false;
}
