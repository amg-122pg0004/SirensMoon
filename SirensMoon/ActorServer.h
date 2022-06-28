/*****************************************************************//**
 * \file   ActorServer.h
 * \brief  全てのアクターを動的配列_typeActorsに入れて管理します。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <memory>
#include <vector>
#include "Actor.h"

//#include "Game.h"

class Actor;
class Game;

class ActorServer {

	public:
		ActorServer();

		typedef std::vector<std::unique_ptr<Actor>> TypeActors;
		TypeActors& GetObjects() { return _typeActors; }

		void Clear();

		/** Actorをペンディングに追加する */
		void Add(std::unique_ptr<Actor> actor);
		void Delete(Actor& actor);

		
		void Update(); //<各アクターのUpdateを呼び出す
		void Render(); //<各アクターのRenderを呼び出す

	private:
		//Game& _game;
		TypeActors _typeActors;
		TypeActors _pendingTypeActors;

		/*Actors範囲ループが回っていない事を確認するためのフラグ*/
		bool _updating; 

		/*ペンディングのActorをゲーム内に追加*/
		void AddPendingActors();

		void DeleteObjects();

};
