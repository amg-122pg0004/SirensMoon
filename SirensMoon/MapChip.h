#pragma once
#include "Game.h"
#include "picojson/picojson.h"
#include "Math.h"

class Game;
class SplitWindow;

class MapChip{
	public:
		MapChip(Game& game);
		~MapChip();
		int LoadMap(const char *jasonfile);

		/**
		 * \brief �}�b�v�R���W�����̍X�V���s���܂��B
		 */
		void Update();


		/**
		 * \brief �^�C���̕\�����s���֐�
		 * 
		 * \param windowPos ������ʂ̍���̍��W
		 * \param cameraPos �J�����̍��W(��{�I��0,0)
		 */
		void Render(Vector2 windowPos,Vector2 cameraPos);

	private:
		Game& _game;

		int _mapSize_W;
		int _mapSize_H;
		int _mapSize_Layer;

		int _chipCount;
		int _chipCount_W;
		int _chipCount_H;
		
		int _chipSize_W;
		int _chipSize_H;

		int* _nMap;

		int* _cgChip;
};
