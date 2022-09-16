/*****************************************************************//**
 * \file   Game.h
 * \brief  �v���Z�X���Ǘ����܂��B
 *
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/

#pragma once
#include <memory>
#include <vector>
#include "InputManager.h"
#include "ModeServer.h"

constexpr int screen_W{ 1920 };//<�E�B���h�E�̉𑜓x�F��
constexpr int screen_H{ 1080 };//<�E�B���h�E�̉𑜓x�F�c
constexpr int screen_Depth{ 32 };//<�E�B���h�E�̐F��(bit)
constexpr int splitscreen_W{ screen_W / 2 - 30 };

class Game {

public:
	enum class Progress {
		StartUp1,
		StartUp2,
		StartUp3,
		Intro,
		StartMenu,
		Stage1,
		Stage1Clear,
		Stage2,
		Stage2Clear,
		Stage3,
		Stage3Clear,
		Credit
	};

	Game();//<Game�R���X�g���N�^
	void Input();//<���͂̎擾
	void Update();//<�v�Z�A�X�V
	void Render();//<�`��X�V
	void Debug();//<�f�o�b�O�p�\��
	void RestartMode();
	void NextMode();
	void GameOver();
	/**
	 * @brief �C���v�b�g�}�l�[�W���[�̎擾
	 * @return �C���v�b�g�}�l�[�W���[�̎Q�Ƃ�Ԃ�
	 */
	inline  auto GetInputManager() { return _inputManager; }

	inline int GetFrameCount() { return _frameCount; }

	std::unique_ptr<ModeServer>& GetModeServer() { return _modeServer; }
	Progress GetProgress() { return _progress; }
	void PlayStartUp1();
	void PlayStartUp2();
	void PlayStartUp3();
	void PlayIntro();
	void PlayStartMenu();
	void PlayStage1();
	void PlayStage1Clear();
	void PlayStage2();
	void PlayStage2Clear();
	void PlayStage3();
	void PlayStage3Clear();
	void PlayCredit();

private:
	std::shared_ptr<InputManager> _inputManager;
	std::unique_ptr<ModeServer> _modeServer;
	int _frameCount;
	bool _debug;
	Progress _progress;
};