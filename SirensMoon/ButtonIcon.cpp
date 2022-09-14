#include "ButtonIcon.h"
#include "Actor.h"
#include "ModeGame.h"
#include "Gimmick.h"
#include "Switch.h"
#include "StickeyBomb.h"
#include "ServerMachine.h"
#include "DegitalLetter.h"
#include "BigServer.h"
#include "BigGenerator.h"
#include "BigGun.h"

ButtonIcon::ButtonIcon(Game& game, ModeBase& mode, Vector2 pos, Vector2 size, int playerno)
	:UIBase(game, mode, pos, size), _playerno{ playerno },_owner{nullptr}
{
	_font = CreateFontToHandle("ButtonIconFont", 20, 9, -1);
	_cg_A = ImageServer::LoadGraph("resource/UI/Button/A.png");
	_cg_B = ImageServer::LoadGraph("resource/UI/Button/B.png");
	_cg_X = ImageServer::LoadGraph("resource/UI/Button/X.png");
	_cg_Y = ImageServer::LoadGraph("resource/UI/Button/Y.png");


}

void ButtonIcon::Update() {
	if (_owner == nullptr) {
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
		return;
	}

	if (_playerno == 0) {
		for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
			if (actor->GetType() == Actor::Type::PlayerA) {
				if (!actor->GetVisibility()) {
					return;
				}
			}
		}
	}
	else {
		for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
			if (actor->GetType() == Actor::Type::PlayerB) {
				if (!actor->GetVisibility()) {
					return;
				}
			}
		}
	}

	if (_playerno == 0) {
		for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
			if (actor->GetType() == Actor::Type::Gimmick) {
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::Switch){
					if (dynamic_cast<Switch&>(*actor).GetAccessible1()) {
						_visible = true;
						_message = "スイッチに触れる";
						return;
					}
				}
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::StickyBomb) {
					if (dynamic_cast<StickyBomb&>(*actor).GetAccessible1()) {
						_visible = true;
						_message = "爆弾を外す";
						return;
					}
				}
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::DegitalLetter) {
					if (dynamic_cast<DegitalLetter&>(*actor).GetAccessible1()) {
						_visible = true;
						_message = "デジタルレターに触れる";
						return;
					}
				}
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigGenerator) {
					if (dynamic_cast<BigGenerator&>(*actor).GetAccessible()) {
						_visible = true;
						_message = "発電機を起動する";
						return;
					}
				}
				
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigGun) {
					if (dynamic_cast<BigGun&>(*actor).GetAccesible()) {
						_visible = true;
						_message = "レールガンに乗り込む";
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
						_message = "スイッチに触れる";
						return;
					}
				}
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::StickyBomb) {
					if (dynamic_cast<StickyBomb&>(*actor).GetAccessible2()) {
						_visible = true;
						_message = "爆弾を外す";
						return;
					}
				}
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::DegitalLetter) {
					if (dynamic_cast<DegitalLetter&>(*actor).GetAccessible2()) {
						_visible = true;
						_message = "デジタルレターに触れる";
						return;
					}
				}
				if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::BigServer) {
					if (dynamic_cast<BigServer&>(*actor).GetAccessible()) {
						_visible = true;
						_message = "発電機を起動する";
						return;
					}
				}
			}
			if (actor->GetType() == Actor::Type::Server) {
				if (dynamic_cast<ServerMachine&>(*actor).GetAccesible()) {
					_visible = true;
					_message = "サーバーにアクセスする";
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

		std::stringstream ss;
		ss << _message;

		DrawStringToHandle(static_cast<int>(col_center.x - camera_pos.x + window_pos.x- _message.size()*5),
			static_cast<int>(col_center.y - camera_pos.y + window_pos.y - _size.y*3/4),
			ss.str().c_str(), GetColor(255, 255, 255), _font);

		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawExtendGraph(static_cast<int>(col_center.x - camera_pos.x + window_pos.x-_size.x / 2),
			static_cast<int>(col_center.y - 80 - camera_pos.y + window_pos.y - _size.y / 2),
			static_cast<int>(col_center.x - camera_pos.x + window_pos.x+_size.x/2),
			static_cast<int>(col_center.y - 80 - camera_pos.y + window_pos.y+_size.y/2),
			_cg_A, 1);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}