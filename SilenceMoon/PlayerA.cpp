#include "PlayerA.h"
#include "RedBullet.h"
#include "GreenBullet.h"
#include "ModeGame.h"
#include "FX_Chargein.h"
#include "FX_Chargenow.h"
#include "LaserLight.h"
#include "FX_Teleport.h"
#include "MiniShuttle.h"
PlayerA::PlayerA(Game& game, ModeGame& base, int playernum) 
	:Player(game, base, playernum),_setGreenBullet{false},_bullet{ 5 }
	,_charge{ 0 }, _cooldown{ 0 },_gameoverCountDown{180}, _bulletMAX{5}
{
	Load();
}

void PlayerA::Load(){
	std::vector<int> handle;
	handle.resize(81);

	ImageServer::LoadDivGraph("resource/Player/PlayerA/Wait/back.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Wait/front.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Wait/left.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Wait/right.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Right}] = handle;

	ImageServer::LoadDivGraph("resource/Player/PlayerA/Walk/back.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Walk/front.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Walk/left.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Walk/right.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Right}] = handle;
	handle.resize(60);
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/back.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/front.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/left.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/right.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Right}] = handle;

	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/backleft.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::UpLeft}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/backright.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::UpRight}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/frontleft.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::DownLeft}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/frontright.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::DownRight}] = handle;

	handle.resize(16);
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Set/back.png", 16, 8, 2, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Set/front.png", 16, 8, 2, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Set/left.png", 16, 8, 2, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Set/right.png", 16, 8, 2, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Right}] = handle;

	handle.resize(41);
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Shoot/back.png", 41, 10, 5, 150, 150, handle.data());
	_cg[{PlayerState::Shoot, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Shoot/front.png", 41, 10, 5, 150, 150, handle.data());
	_cg[{PlayerState::Shoot, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Shoot/left.png", 41, 10, 5, 150, 150, handle.data());
	_cg[{PlayerState::Shoot, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Shoot/right.png", 41, 10, 5, 150, 150, handle.data());
	_cg[{PlayerState::Shoot, PlayerDirection::Right}] = handle;

	handle.resize(41);
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Action/back.png", 21, 7, 3, 150, 150, handle.data());
	_cg[{PlayerState::Access, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Action/front.png", 21, 7, 3, 150, 150, handle.data());
	_cg[{PlayerState::Access, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Action/left.png", 21, 7, 3, 150, 150, handle.data());
	_cg[{PlayerState::Access, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Action/right.png", 21, 7, 3, 150, 150, handle.data());
	_cg[{PlayerState::Access, PlayerDirection::Right}] = handle;
}

void PlayerA::Action(){

	if (_inputManager->CheckInput("BULLET1", 't', _playerNum)&&_charge==0 ) {
		_setGreenBullet = true;
		PlaySoundMem(SoundServer::Find("ChangeAmmo"), DX_PLAYTYPE_BACK);
	}
	if (_inputManager->CheckInput("BULLET2", 't', _playerNum) && _charge == 0) {
		_setGreenBullet = false;
		PlaySoundMem(SoundServer::Find("ChangeAmmo"), DX_PLAYTYPE_BACK);
	}

	if (_inputManager->CheckInput("ACCESS", 't', _playerNum) && _movable) {
		OnMiniShuttle();
	}


	--_cooldown;
	if (_cooldown > 180-30) {
		_state = PlayerState::Shoot;

		std::vector<int> cg = _cg[{_state, _direction}];

	}
	if (_cooldown == 160) {
		_movable = true;
	}
	if (_cooldown < 0) {
		_cooldown = 0;
	}

	if (_inputManager->CheckInput("ACCESS", 't', _playerNum) && _charge>0) {
		_charge = 0;
		_cooldown = 30;
	}

	if (_inputManager->CheckInput("ACTION", 'r', _playerNum)) {
		_slow = false;
		if (_charge >= 120) {
			if (_bullet > 0) {
				if (_setGreenBullet) {
					auto bullet = std::make_unique<GreenBullet>(_game, _mode, _pos, _inputAngle);
					_mode.GetActorServer().Add(std::move(bullet));
				}
				else {
					auto bullet = std::make_unique<RedBullet>(_game, _mode, _pos, _inputAngle);
					_mode.GetActorServer().Add(std::move(bullet));
				}


				PlaySoundMem(SoundServer::Find("Fire"), DX_PLAYTYPE_BACK);
				_cooldown = 180;
				_speed = { 0,0 };
				_speed2 = 0;
				_movable = false;
				_state = PlayerState::Shoot;
				_animNo = 0;
				--_bullet;


			}
		}
	}

	if (_inputManager->CheckInput("ACTION", 'h', _playerNum) && _cooldown == 0 && _visible) {
		if (_charge >= 120) {
			StartJoypadVibration(DX_INPUT_PAD1, 200, 50, -1);
		}
		else {
			StartJoypadVibration(DX_INPUT_PAD1, 50, 50, -1);
		}

		//_movable = false;
		_slow = true;
		_state = PlayerState::Set;
		if (_charge == 0) {

			_animNo = 0;
			auto gunlight = std::make_unique<LaserLight>(_game, _mode, *this);
			_mode.GetActorServer().Add(std::move(gunlight));
		}

		++_charge;
		if (_charge == 1) {
			PlaySoundMem(SoundServer::Find("Charging"), DX_PLAYTYPE_BACK);
			_mode.GetActorServer().Add(std::make_unique<FX_Chargein>(_game, _mode, _pos, _game.GetFrameCount(),*this));
		}
		if (_charge == 105) {
			PlaySoundMem(SoundServer::Find("Chargekeep"), DX_PLAYTYPE_LOOP);
			_mode.GetActorServer().Add(std::make_unique<FX_Chargenow>(_game, _mode, _pos, _game.GetFrameCount(), *this));
		}

	}
	else {
		if (_cooldown == 132) {
			_movable = true;
		}
		_charge = 0;
		StopSoundMem(SoundServer::Find("Chargekeep"));
		StopSoundMem(SoundServer::Find("Charging"));
	}
	Player::DirectionCGStateUpdate();
	if (_bullet <= 0) {
		--_gameoverCountDown;
		if (_gameoverCountDown <= 0) {
			_mode.GameOver();
		}
	}
}

void PlayerA::TakeAmmo() {
	++_bullet;
	if (_bullet > _bulletMAX) {
		_bullet = _bulletMAX;
	}
}

void PlayerA::AnimUpdate(){

	if (_speed.Length() < 0.1) {
		_state = PlayerState::Wait;
	}
	else if (_speed.Length() < 2.8) {
		if (_state == PlayerState::Wait) {
			if (CheckSoundMem(SoundServer::Find("Walking")) == 0) {
				PlaySoundMem(SoundServer::Find("Walking"), DX_PLAYTYPE_BACK);
			}
		}
		_state = PlayerState::Walk;
	}
	else {
		_state = PlayerState::Run;
	}

	Player::DirectionCGStateUpdate();
}

void PlayerA::TeleportEvent() {
	/*テレポート用のディレイ*/
	--_teleportDelay;
	
	if (_teleportDelay == 135) {
		_mode.GetActorServer().Add(std::make_unique<FX_TeleportIN1>(_game, _mode, _preTeleportPosition, _game.GetFrameCount()));
	}
	else if (_teleportDelay == 68) {
		_pos=_teleportPosition;
		auto&& rendercamera = _mode.GetSplitWindow()[_playerNum]->GetCamera();
		rendercamera->SetPosition(_pos);
		_mode.GetActorServer().Add(std::make_unique<FX_TeleportOUT1>(_game, _mode, _pos, _game.GetFrameCount()));
	}
	else if (_teleportDelay == 30) {
		_movable = true;
		_visible = true;
	}
	
}

void PlayerA::OnMiniShuttle(){
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::Gimmick) {
			if (static_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::MiniShuttle) {
				if (!static_cast<MiniShuttle&>(*actor).GetAccessible()) {
					break;
				}
				_movable = false;
				_visible = false;
				_invincibleTime = 600;
				static_cast<MiniShuttle&>(*actor).SetAnimation(true);
				_teleportPosition = { 3333,4000 };
			}
		}
	}
}

void PlayerA::OffMiniShuttle() {
	_movable = true;
	_visible = true;
}

void PlayerA::TargetSpawnEvent() {
	_setGreenBullet = true;
	if (_charge > 0) {
		_charge = 0;
		_cooldown = 30;
	}
}

void PlayerA::TakeDamage(Actor::Type type) {
	_slow = false;
	Player::TakeDamage(type);
}