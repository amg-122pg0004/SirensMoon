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
#include "Math.h"
#include "Actor.h"

class ModeBase;
//class Actor;


class ActorServer {

	public:
		ActorServer(ModeBase&);

		typedef std::vector<std::unique_ptr<Actor>> TypeActors;
		TypeActors& GetObjects() { return _typeActors; }

		void Clear();

		/** Actorをペンディングに追加する */
		void Add(std::unique_ptr<Actor> actor);
		void Delete(Actor& actor);

		
		void Update(); //<各アクターのUpdateを呼び出す
		void StandardRender(int stageNum,Vector2 windowPos, Vector2 cameraPos); //<各アクターのRenderを呼び出す
		void ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);

		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);


	private:
		TypeActors _typeActors;
		TypeActors _pendingTypeActors;

		/*Actors範囲ループが回っていない事を確認するためのフラグ*/
		bool _updating; 

		/*ペンディングのActorをゲーム内に追加*/
		void AddPendingActors();

		void DeleteObjects();

		ModeBase& _mode;

};
