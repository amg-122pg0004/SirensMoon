#include "BigGenerator.h"
#include "SignalLight.h"
#include "ModeGame.h"
#include "BossGimmickController.h"
#include <sstream>

BigGenerator::BigGenerator(Game& game, ModeGame& mode, ObjectDataStructs::BigGeneratorData data, BossGimmickController& controller)
	:Gimmick(game,mode,data.ID),_span{20},_elapsed{0},_flash{false},_index{0},_pattern{-1},_signal{false},_controller{controller}
{
	_pos = data.pos;
	auto light=std::make_unique<SignalLight>(game,mode,*this);
	_mode.GetActorServer().Add(std::move(light));
	_activate = false;
	_cg_passive = ImageServer::LoadGraph("resource/Gimmick/biggen.png");
	_cg_active = ImageServer::LoadGraph("resource/Gimmick/biggen2.png");
	int X, Y;
	GetGraphSize(_cg_passive,&X,&Y);
	_size = { static_cast<double>(X), static_cast<double>(Y) };
	UpdateCollsiion();
	Vector2 fix = { 10, 10 };
	_accessArea.min = _collision.min - fix;
	_accessArea.max = _collision.max + fix;
}

void BigGenerator::Update() {

	++_elapsed;
	if (_elapsed > _span) {
		++_index;
		_elapsed = 0;
	}
	if (_index >= _signal.size()) {
		_index = 0;
	}
	_flash = _signal[_index];

	if (CheckHitBullet()) {
		_activate = true;
		_controller.RecieveStartGenerator(_pattern);
	}

}

bool BigGenerator::CheckHitBullet() {
	for (auto&& actor : _mode.GetObjects()) {
		auto type = actor->GetType();
		if (type == Actor::Type::PlayerA) {
			if (Intersect(_accessArea, actor->GetCollision())) {
				if (_game.GetInputManager()->CheckInput("ACCESS", 't', 0)) {
					return true;
				}
			}
		}
		/*
		if (type == Actor::Type::RedBullet || type == Actor::Type::GreenBullet) {
			if(Intersect(_collision, actor->GetCollision()) ){

				actor->Dead();
				return true;
			}
		}
		*/
	}
	return false;
}

void BigGenerator::StandardRender(Vector2 window_pos, Vector2 camera_pos){
	if (_activate) {
		_cg = _cg_active;
	}
	else {
		_cg = _cg_passive;
	}

	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg, 1);
}

void BigGenerator::Debug(Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(window_pos, camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);

	std::stringstream ss;
	ss << "activate"<<_activate<<"\n";
	ss << "flash" << _flash << "\n";

	DrawString(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
		static_cast<int>(_pos.y-camera_pos.y + window_pos.y),
		ss.str().c_str(), GetColor(255, 255, 255));
}

void BigGenerator::UpdateCollsiion(){
	_collision.min = _pos;
	_collision.max = _pos + _size;
}

void BigGenerator::SetPattern(int pattern, std::vector<bool> signal){
	_pattern = pattern;
	_signal = signal;
	_activate = false;
	_cg = _cg_active;
}