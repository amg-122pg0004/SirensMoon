#include "ServerMachine.h"
#include <random>
#include "Game.h"
#include "ModeGame.h"

#include "InputManager.h"
#include "EnemyVIP.h"
#include "SplitWindow.h"
#include "ServerMachineUI.h"
#include "SoundServer.h"

ServerMachine::ServerMachine(Game& game, ModeGame& mode, ObjectDataStructs::ServerMachineData data, EnemyGenerator::EnemyPattern pattern)
	:Actor(game, mode),_valid{false},_serverData{data},_energy{0}, _pattern{pattern},_deadVIP{false}
{
	_inputManager = _game.GetInputManager();
	_accessArea.min = {0,0};
	_accessArea.max = {0,0};
	_cg_up = ImageServer::LoadGraph("resource/Server/up.png");
	_cg_right = ImageServer::LoadGraph("resource/Server/right.png");
	_cg_down = ImageServer::LoadGraph("resource/Server/down.png");
	_cg_left = ImageServer::LoadGraph("resource/Server/left.png");
	_pos = _serverData.Position;
	
	if (_serverData.Direction == "up") {
		_cg = _cg_up;
	}else 	if(_serverData.Direction == "down") {
		_cg = _cg_down;
	}else if(_serverData.Direction == "right") {
		_cg = _cg_right;
	}else if(_serverData.Direction == "left") {
		_cg = _cg_left;
	}

	int x, y;
	GetGraphSize(_cg,&x,&y);
	_size = { static_cast<double>(x),static_cast<double>(y) };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	if (_serverData.Direction == "up") {
		_accessArea.min = { _pos.x ,_pos.y - 10 };
		_accessArea.max = { _pos.x + _size.x , _pos.y + _size.y };
	}
	else 	if (_serverData.Direction == "right") {
		_accessArea.min = { _pos.x + _size.x,_pos.y };
		_accessArea.max = { _pos.x + _size.x + 10,_pos.y + _size.y };
	}
	else if (_serverData.Direction == "down") {
		_accessArea.min = { _pos.x,_pos.y + _size.y };
		_accessArea.max = { _pos.x + _size.x,_pos.y + _size.y + 10 };
	}
	else if (_serverData.Direction == "left") {
		_accessArea.min = { _pos.x - 10,_pos.y };
		_accessArea.max = { _pos.x,_pos.y + _size.y };
	}

	Vector2 map_pos = { 1080,660 };
	Vector2 map_size = { 780,420 };
	
	std::vector<std::unique_ptr<SplitWindow>>& spw = dynamic_cast<ModeGame&>(_mode).GetSplitWindow();
	auto window = std::make_unique<ServerMachineUI>(_game, _mode, map_pos, map_size, *this,_pattern);
	spw[1]->GetUIServer().emplace_back(std::move(window));
}


void ServerMachine::Update() {
	if (_deadVIP == false) {
		if ((_inputManager->CheckInput("ACCESS", 't', 1))) {
			for (auto&& actor : _mode.GetActorServer().GetObjects()) {
				if (actor->GetType() == Type::PlayerB) {
					if (Intersect(_accessArea, actor->GetCollision())) {
						_energy += 50;
						break;
					}
				}
			}
		}
		if (_energy > 300) {
			_energy = 300;
		}
		_energy -= 3;
		if (_energy < 0) {
			_energy = 0;
		}
		if (_energy > 0) {
			//PlaySoundMem(SoundServer::Find("PlayerOpenMap"), DX_PLAYTYPE_BACK);
			if (_valid == false) {
				_valid = true;
				SpawnEnemyVIP();
			}
		}
		if (_energy == 0) {
			_valid = false;
		}
	}
}

void ServerMachine::ChangeValidFlag(bool flag) {
	_valid = flag;
}

void ServerMachine::SpawnEnemyVIP() {
	Vector2 player0pos={0,0};
	for (auto&& actor:_mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::Player) {
			auto player =dynamic_cast<Player&>(*actor);
			if (player.GetPlayerNum() == 0) {
				player0pos=player.GetPosition();
			}
		}
	}

	int count_x=static_cast<int>(ceil(player0pos.x / 960));
	int count_y= static_cast<int>(ceil(player0pos.y / 1080));
	int count_x2 = static_cast<int>(ceil(_pos.x / 960));
	int count_y2 = static_cast<int>(ceil(_pos.y / 1080));

	ModeGame& mode = dynamic_cast<ModeGame&>(_mode);
	auto vipdata = mode.GetMapChips()->GetPatrolPointsVIP();

	if (vipdata.size() < 4) {
		return;
	}

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(vipdata.begin(), vipdata.end(), engine);


	int i = 0;
	for (i; i < vipdata.size(); ++i) {
		auto pos = vipdata[i].PatrolPoints[0];
		int count_x3 = static_cast<int>(ceil(pos.x / (static_cast<double>(screen_W) / 2)));
		int count_y3 = static_cast<int>(ceil(pos.y / screen_H));
		if (count_x3 != count_x || count_y3 != count_y) {
			if (count_x3 != count_x2 || count_y3 != count_y2) {
				break;
			}
		}
	}
	auto loot = vipdata[i];
	Vector2 pos=loot.PatrolPoints[0];
	auto id = loot.ID;
	ObjectDataStructs::EnemyData data = { id,0,pos,0 };
	auto enemy = std::make_unique<EnemyVIP>(_game, _mode, data, *this,loot, _pattern);
	mode.GetActorServer().Add(std::move(enemy));

}

void ServerMachine::DeadEnemyVIP() {
	_energy = 0;
	_deadVIP = true;
	ModeGame& mode=dynamic_cast<ModeGame&>(_mode);
	mode.StageClearCheck();
}

void ServerMachine::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(stageNum, window_pos, camera_pos);
	_accessArea.Draw2(stageNum,window_pos,camera_pos);
	
	std::stringstream ss;
	ss << "�G�l���M�[" << _energy;
	DrawString(500,500, ss.str().c_str(), GetColor(255, 0, 255));
}