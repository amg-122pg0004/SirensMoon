#include "ServerMachine.h"
#include "InputManager.h"
#include "ImageServer.h"
#include "Game.h"
#include "ModeBase.h"
#include "ModeGame.h"
#include <memory>
#include <random>

#include "SplitWindow.h"
#include "ServerMachineUI.h"
#include "SoundServer.h"

ServerMachine::ServerMachine(Game& game, ModeBase& mode, MapChips::ServerMachineData data)
	:Actor(game, mode),_valid{false},_serverData{data},_energy{0}
{
	_inputManager = _game.GetInputManager();
	_accessArea.min = {0,0};
	_accessArea.max = {0,0};
	_cg_up = ImageServer::LoadGraph("resource/Server/up.png");
	_cg_right = ImageServer::LoadGraph("resource/Server/right.png");
	_cg_down = ImageServer::LoadGraph("resource/Server/down.png");
	_cg_left = ImageServer::LoadGraph("resource/Server/left.png");
	_pos = _serverData.Position;
	
	switch (_serverData.Direction) {
		case 1:
			_cg = _cg_up;
		case 2:
			_cg = _cg_right;
		case 3:
			_cg = _cg_down;
		case 4:
			_cg = _cg_left;
	}
	int x, y;
	GetGraphSize(_cg,&x,&y);
	_size = { static_cast<double>(x),static_cast<double>(y) };
	_collision.min = _pos;
	_collision.max = _pos + _size;

	switch (_serverData.Direction) {
		case 1:
			_accessArea.min = { _pos.x ,_pos.y - 10 };
			_accessArea.max = { _pos.x + _size.x , _pos.y + _size.y };
		case 2:
			_accessArea.min = { _pos.x + _size.x,_pos.y };
			_accessArea.max = { _pos.x + _size.x + 10,_pos.y + _size.y };
		case 3:
			_accessArea.min = { _pos.x,_pos.y + _size.y };
			_accessArea.max = { _pos.x + _size.x,_pos.y + _size.y + 10 };
		case 4:
			_accessArea.min = { _pos.x - 10,_pos.y };
			_accessArea.max = { _pos.x,_pos.y + _size.y };
	}

	Vector2 map_pos = { 1080,660 };
	Vector2 map_size = { 780,420 };
	
	std::vector<std::unique_ptr<SplitWindow>>& spw = dynamic_cast<ModeGame&>(_mode).GetSplitWindow();
	auto window = std::make_unique<ServerMachineUI>(_game, _mode, map_pos, map_size, *this);
	spw[1]->GetUIServer().emplace_back(std::move(window));
	
	_generatedEnemy.resize(3);
	_generatedEnemy = { -1,-1,-1 };
	GenerateEnemy();
}


void ServerMachine::Update() {
	if ((_inputManager->CheckInput("ACCESS", 't', 1))) {
		for (auto&& actor : _mode.GetActorServer().GetObjects()) {
			if (actor->GetType() == Type::Player) {
				Player player = dynamic_cast<Player&>(*actor);
				if (player.GetPlayerNum() == 1 && Intersect(_accessArea, actor->GetCollision())) {
					_energy += 50;
					break;
				}
			}
		}
	}
	if (_energy >300) {
		_energy = 300;
	}
	_energy-=3;
	if (_energy < 0) {
		_energy = 0;
	}
	if(_energy > 0 ) {
		//PlaySoundMem(SoundServer::Find("PlayerOpenMap"), DX_PLAYTYPE_BACK);
		if (_valid == false) {
			_valid = true;
			SpawnEnemyVIP();
		}
	}
	if(_energy==0) {
		_valid = false;
	}

}

void ServerMachine::ChangeValidFlag(bool flag) {
	_valid = flag;
}

void ServerMachine::GenerateEnemy() {
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand3(1, 3);

	_generatedEnemy[0] = rand3(mt);
	_generatedEnemy[1] = rand3(mt);
	_generatedEnemy[2] = rand3(mt);

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
	int count_x=ceil(player0pos.x / 960);
	int count_y=ceil(player0pos.y / 1080);
	int count_x2 = ceil(_pos.x / 960);
	int count_y2 = ceil(_pos.y / 1080);

	ModeGame& mode = dynamic_cast<ModeGame&>(_mode);
	auto vipdata = mode.GetMapChips()->GetPatrolPointsVIP();
	int random = _game.GetFrameCount() % vipdata.size();

	auto loot = vipdata[random];
	auto pos = loot.PatrolPoints[0];
	auto id = loot.ID;
	MapChips::EnemyData data = { id,0,pos,0 };
	auto enemy = std::make_unique<EnemyVIP>(_game, _mode, data, *this,loot);
	mode.GetActorServer().Add(std::move(enemy));

}

void ServerMachine::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(stageNum, window_pos, camera_pos);
	_accessArea.Draw2(stageNum,window_pos,camera_pos);
}