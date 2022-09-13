#include "Mine.h"
#include "ModeGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Explode.h"

Mine::Mine(Game& game, ModeGame& mode, MineData data)
	:Gimmick(game,mode,data.ID),_dir{data.dir}
{
	_range = data.range;
	_pos = data.pos;
	_size = { 30,30 };
	_collision.min = { 0,0 };
	_collision.max = { 0,0 };

	switch (data.dir) {
		case 1 :
			_detectionArea.min = _pos;
			_detectionArea.max = { _pos.x + _size.x + _range ,_pos.y + _size.y};
			break;
		case 2:
			_detectionArea.min = _pos;
			_detectionArea.max = { _pos.x + _size.x,_pos.y + _size.y + _range };
			break;
		case 3:
			_detectionArea.min = { _pos.x - _range,_pos.y };
			_detectionArea.max = { _pos.x + _size.x , _pos.y + _size.y };
			break;
		case 4:
			_detectionArea.min = { _pos.x , _pos.y - _range };
			_detectionArea.max = { _pos.x + _size.x , _pos.y + _size.y };
			break;
		default:
			_detectionArea.min = _pos;
			_detectionArea.max = _pos+_size;
			break;
	}

	_cg = ImageServer::LoadGraph("resource/Gimmick/mine.png");
}

void Mine::Update(){
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA|| actor->GetType() == Type::PlayerB) {
			if(Intersect(_detectionArea, actor->GetCollision())) {
				//dynamic_cast<Player&>(*actor).TakeDamage(GetType());
				for (int i = 0; i < 4; ++i) {
					Vector2 pos=(_detectionArea.max - _detectionArea.min)*i/4+ _detectionArea.min;
					_mode.GetActorServer().Add(std::make_unique<Explode>(_game, _mode, pos));
				}

				_dead = true;
				PlaySoundMem(SoundServer::Find("ActiveTrapBom"), DX_PLAYTYPE_BACK);
			}
		}
		if (actor->GetType() == Type::Enemy) {
			if (Intersect(_detectionArea, actor->GetCollision())) {
				_dead = true;
				PlaySoundMem(SoundServer::Find("ActiveTrapBom"), DX_PLAYTYPE_BACK);
			}
		}
	}
}

void Mine::StandardRender(Vector2 window_pos, Vector2 camera_pos){
	double angle{(_dir - 1) * 3.1415 / 2};
	
	
	DrawRotaGraph(static_cast<int>(_pos.x+(_size.x/2) + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + (_size.y / 2) + window_pos.y - camera_pos.y)
		,1.0
		,angle
		,_cg
		, 1,0);
	
}

void Mine::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_detectionArea.Draw2(window_pos, camera_pos);
}