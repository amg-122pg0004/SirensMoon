#include "ButtonIcon.h"
#include "Actor.h"
#include "ModeGame.h"
#include "Gimmick.h"
#include "Switch.h"
#include "StickeyBomb.h"
#include "ServerMachine.h"

ButtonIcon::ButtonIcon(Game& game, ModeBase& mode, Vector2 pos, Vector2 size, int playerno)
	:UIBase(game, mode, pos, size), _playerno{ playerno },_owner{nullptr}
{
	_cg_A = ImageServer::LoadGraph("resource/UI/Button/A.png");
	_cg_B = ImageServer::LoadGraph("resource/UI/Button/B.png");
	_cg_X = ImageServer::LoadGraph("resource/UI/Button/X.png");
	_cg_Y = ImageServer::LoadGraph("resource/UI/Button/Y.png");

	for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
		if (_playerno == 0) {
			if (actor->GetType() == Actor::Type::PlayerA) {
				_owner = actor.get();
			}
		}
		else {
			if (actor->GetType() == Actor::Type::PlayerB) {
				_owner = actor.get();
			}
		}
	}
}

void ButtonIcon::Update() {
	if (_playerno == 0) {
		for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
			if (actor->GetType() == Actor::Type::Gimmick) {
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::Switch){
					if (dynamic_cast<Switch&>(*actor).GetAccessible1()) {
						_visible = true;
						return;
					}
				}
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::StickyBomb) {
					if (dynamic_cast<StickyBomb&>(*actor).GetAccessible1()) {
						_visible = true;
						return;
					}
				}
			}
		}
	}
	else {
		for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
			if (actor->GetType() == Actor::Type::Gimmick) {
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::Switch) {
					if (dynamic_cast<Switch&>(*actor).GetAccessible2()) {
						_visible = true;
						return;
					}
				}
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::StickyBomb) {
					if (dynamic_cast<StickyBomb&>(*actor).GetAccessible2()) {
						_visible = true;
						return;
					}
				}
			}
			if (actor->GetType() == Actor::Type::Server) {
				if (dynamic_cast<ServerMachine&>(*actor).GetAccesible()) {
					_visible = true;
					return;
				}
			}
		}
	}

	_visible = false;
}

void ButtonIcon::Render() {
	if (_visible) {
		auto col=_owner->GetCollision();
		auto col_center = (col.min + col.max) / 2;
		auto&& window = dynamic_cast<ModeGame&>(_mode).GetSplitWindow()[_playerno];
		auto camera_pos = window->GetCamera()->GetPosition();
		auto window_pos=window->GetWindowPos();

		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawExtendGraph(static_cast<int>(col_center.x - camera_pos.x + window_pos.x-_size.x / 2),
			static_cast<int>(col_center.y - 80 - camera_pos.y + window_pos.y - _size.y / 2),
			static_cast<int>(col_center.x - camera_pos.x + window_pos.x+_size.x/2),
			static_cast<int>(col_center.y - 80 - camera_pos.y + window_pos.y+_size.y/2),
			_cg_A, 1);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}