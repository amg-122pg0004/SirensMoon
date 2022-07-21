/*****************************************************************//**
 * \file   ModeBase.h
 * \brief  モードの親クラスです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "ActorServer.h"

class Game;

class ModeBase {
public:
	ModeBase(Game& game);
	virtual ~ModeBase();

	virtual void Update();  // 更新
	virtual void Render();	// 描画
	virtual void Debug(); //デバッグ

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
