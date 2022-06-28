/*****************************************************************//**
 * \file   ActorServer.h
 * \brief  �S�ẴA�N�^�[�𓮓I�z��_typeActors�ɓ���ĊǗ����܂��B
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <memory>
#include <vector>
#include "Actor.h"
#include "Math.h"

class Actor;
class Game;

class ActorServer {

	public:
		ActorServer();

		typedef std::vector<std::unique_ptr<Actor>> TypeActors;
		TypeActors& GetObjects() { return _typeActors; }

		void Clear();

		/** Actor���y���f�B���O�ɒǉ����� */
		void Add(std::unique_ptr<Actor> actor);
		void Delete(Actor& actor);

		
		void Update(); //<�e�A�N�^�[��Update���Ăяo��
		void Render(Vector2 windowPos, Vector2 cameraPos); //<�e�A�N�^�[��Render���Ăяo��

	private:
		TypeActors _typeActors;
		TypeActors _pendingTypeActors;

		/*Actors�͈̓��[�v������Ă��Ȃ������m�F���邽�߂̃t���O*/
		bool _updating; 

		/*�y���f�B���O��Actor���Q�[�����ɒǉ�*/
		void AddPendingActors();

		void DeleteObjects();

};
