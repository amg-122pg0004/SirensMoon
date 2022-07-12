#pragma once
#include "ActorServer.h"

class Game;

class ModeBase {
public:
	ModeBase(Game& game);
	virtual ~ModeBase();

	virtual void Update();  // çXêV
	virtual void Render();	// ï`âÊ

	std::unique_ptr<ActorServer>& GetActorServer() { return _actorServer; }
	virtual ActorServer::TypeActors GetObjects() { return _actorServer->GetObjects(); }

	virtual bool	IsDead() { return _dead; }
	virtual void	Dead() { _dead = true; }

protected:
	Game& _game;
	bool	_dead;
	std::unique_ptr<ActorServer> _actorServer;

};
