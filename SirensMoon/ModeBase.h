#pragma once
#include "ActorServer.h"

class Game;

class ModeBase {
public:
	ModeBase(Game& game);
	virtual ~ModeBase();

	virtual void Update();  // �X�V
	virtual void Render();	// �`��
	virtual void Debug(); //�f�o�b�O

	//virtual std::unique_ptr<ActorServer>& GetActorServer() { return _actorServer; }
	//virtual ActorServer::TypeActors GetObjects() { return _actorServer->GetObjects(); }
	virtual ActorServer& GetActorServer() { return _actorServer; }
	 virtual ActorServer::TypeActors& GetObjects() { return _actorServer.GetObjects(); }

	virtual bool	IsDead() { return _dead; }
	virtual void	Dead() { _dead = true; }

protected:
	Game& _game;
	bool	_dead;
	//std::unique_ptr<ActorServer> _actorServer;
	ActorServer _actorServer;

};
