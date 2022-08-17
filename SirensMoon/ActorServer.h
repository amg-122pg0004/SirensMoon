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

		/** Actor���y���f�B���O�ɒǉ����� */
		void Add(std::unique_ptr<Actor> actor);
		void Delete(Actor& actor);

		
		void Update(); //<�e�A�N�^�[��Update���Ăяo��
		void StandardRender(int stageNum,Vector2 windowPos, Vector2 cameraPos); //<�e�A�N�^�[��Render���Ăяo��
		void ReconRender(int stageNum, Vector2 windowPos, Vector2 cameraPos);

		void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos);


	private:
		TypeActors _typeActors;
		TypeActors _pendingTypeActors;

		/*Actors�͈̓��[�v������Ă��Ȃ������m�F���邽�߂̃t���O*/
		bool _updating; 

		/*�y���f�B���O��Actor���Q�[�����ɒǉ�*/
		void AddPendingActors();

		void DeleteObjects();

		ModeBase& _mode;

};
