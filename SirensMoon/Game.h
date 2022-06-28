/*****************************************************************//**
 * \file   Game.h
 * \brief  �v���Z�X���Ǘ����܂��B
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <DxLib.h>
#include <memory>
#include <vector>
#include "InputManager.h"
#include "MapChip.h"
#include "Math.h"
#include "SplitWindow.h"
#include "ActorServer.h"
#include "Player.h"

class Camera;
class MapChip;
class SplitWindow;
class ActorServer;


constexpr int screen_W{1600};//<�E�B���h�E�̉𑜓x�F��
constexpr int screen_H{900};//<�E�B���h�E�̉𑜓x�F�c
constexpr int screen_Depth{32};//<�E�B���h�E�̐F��(bit)

class Game {

	public:
		Game();//<Game�R���X�g���N�^
		void Input();//<���͂̎擾
		void Update();//<�v�Z�A�X�V
		void Render();//<�`��X�V
		/**
		 * @brief �C���v�b�g�}�l�[�W���[�̎擾
		 * @return �C���v�b�g�}�l�[�W���[�̎Q�Ƃ�Ԃ�
		 */
		inline std::shared_ptr<InputManager>& GetInputManager() { return _inputManager; }
		inline std::unique_ptr<MapChip>& GetMapChip() { return _mapChip; }

		//ActorServer &GetActorServer() { return _actorServer; }

	private:
		std::shared_ptr<InputManager> _inputManager;
		std::unique_ptr<MapChip>_mapChip;
		std::vector<std::unique_ptr<SplitWindow>>_splitWindow;

	protected:
		ActorServer _actorServer;
};
