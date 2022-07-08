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
#include "Math.h"
#include "InputManager.h"
#include "SplitWindow.h"
#include "ActorServer.h"
#include "Player.h"
#include "MapChip.h"
#include "Camera.h"
#include "ReconPlayer.h"

constexpr int screen_W{1920};//<�E�B���h�E�̉𑜓x�F��
constexpr int screen_H{1080};//<�E�B���h�E�̉𑜓x�F�c
constexpr int screen_Depth{32};//<�E�B���h�E�̐F��(bit)

class Game {

	public:
		Game();//<Game�R���X�g���N�^
		void Input();//<���͂̎擾
		void Update();//<�v�Z�A�X�V
		void Render();//<�`��X�V
		void Debug();//<�f�o�b�O�p�\��

		/**
		 * @brief �C���v�b�g�}�l�[�W���[�̎擾
		 * @return �C���v�b�g�}�l�[�W���[�̎Q�Ƃ�Ԃ�
		 */
		inline  auto GetInputManager() { return _inputManager; }
		inline  auto& GetMapChips() { return _mapChips; }
		inline  auto& GetActorServer() { return _actorServer; }
		inline auto& GetSplitWindow() { return _splitWindow; }

	private:
		std::shared_ptr<InputManager> _inputManager;
		std::unique_ptr<MapChips>_mapChips;
		std::vector<std::unique_ptr<SplitWindow>>_splitWindow;

	protected:
		std::unique_ptr <ActorServer> _actorServer;
};