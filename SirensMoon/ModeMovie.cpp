/*****************************************************************//**
 * \file   ModeMovie.cpp
 * \brief  �Q�[�����Ƀ��[�r�[�������V�[���Ŏg�p���郂�[�h�ł�
 *
 * \author �y�������Y
 * \date   August 2022
 *********************************************************************/
#include "ModeMovie.h"
#include "ImageServer.h"
#include "Game.h"
#include "LoadResources.h"
#include "SkipUI.h"

ModeMovie::ModeMovie(Game& game, std::string path, int skipFrame, bool splitFlag)
	:ModeBase{ game }, _sizeX{ 0 }, _sizeY{ 0 }, _movieSkipFrame{ skipFrame }
	, _bgm{}, _bgmPlayFrame{ -1 }, _splitFlag{ splitFlag }, _loadingNumber{ 0 }, _path{path}
{
	_renderPriority = 10;
	_movieHandle = ImageServer::LoadGraph(path);
	SeekMovieToGraph(_movieHandle, 0);
	PlayMovieToGraph(_movieHandle);

	GetGraphSize(_movieHandle, &_sizeX, &_sizeY);
	_makedNextMode = false;

	SetUseASyncLoadFlag(true);
	Vector2 pos{ 800,0 }, size{ 163,163 };
	_ui.emplace_back(std::make_unique<SkipUI>(_game, *this, *_splitWindow, pos, size));
	LoadResources::LoadSE();
	LoadResources::LoadEffects();
}
ModeMovie::~ModeMovie() {
	PauseMovieToGraph(_movieHandle);
	ImageServer::Erase(_path);
}

void ModeMovie::Update() {
	ModeBase::Update();
	if (GetASyncLoadNum() == 0 && _loadingNumber == 1) {
		if (TellMovieToGraph(_movieHandle) < _movieSkipFrame) {
			VisibleSkipUI();
		}
	}
	_loadingNumber = GetASyncLoadNum();
	if (_loadingNumber == 0 && GetJoypadInputState(DX_INPUT_KEY_PAD1)&& !_game.GetInputManager()->CheckInput("PAUSE", 't', 0) ||
		_loadingNumber == 0 && GetJoypadInputState(DX_INPUT_PAD2)&& !_game.GetInputManager()->CheckInput("PAUSE", 't', 1)) {
		if (TellMovieToGraph(_movieHandle) < _movieSkipFrame) {
			VisibleSkipUI();
		}
	}

	/*PAUSE�{�^���Ŏw��t���[�����܂ŃX�L�b�v*/
	if (_game.GetInputManager()->CheckInput("PAUSE", 't', 0) || _game.GetInputManager()->CheckInput("PAUSE", 't', 1)) {
		if (TellMovieToGraph(_movieHandle) < _movieSkipFrame) {
			auto tesu = TellMovieToGraph(_movieHandle);
			if (_loadingNumber == 0) {
				SeekMovieToGraph(_movieHandle, _movieSkipFrame);
			}
		}
	}
	/*�Z�b�g���ꂽBGM������΍Đ�*/
	PlayBGMInSetFrame();

	/*�Đ����I�������X�L�b�v*/
	if (GetMovieStateToGraph(_movieHandle) == 0) {
		PauseMovieToGraph(_movieHandle);
		ModeBase::NextMode();
	}
	for (auto&& ui : _ui) {
		ui->Update();
	}
}

void ModeMovie::Render() {
	SetDrawArea(0, 0, screen_W, screen_H);
	DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
	if (_splitFlag) {
		DrawExtendGraph(0, 0, splitscreen_W, screen_H, _movieHandle, 0);
		DrawExtendGraph(screen_W - splitscreen_W, 0, screen_W, screen_H, _movieHandle, 0);
	}
	else {
		DrawExtendGraph(0, 0, screen_W, screen_H, _movieHandle, 0);
	}
	for (auto&& ui : _ui) {
		ui->Render();
	}
}

void ModeMovie::Debug() {

}

void ModeMovie::SetBGM(std::string path, int frame) {
	_bgmPlayFrame = frame;
	_bgm = path;
}

void ModeMovie::PlayBGMInSetFrame() {
	if (_bgm.empty()) {
		return;
	}
	if (CheckSoundFile()) {
		return;
	}
	if (_bgmPlayFrame < TellMovieToGraph(_movieHandle)) {
		PlaySoundFile(_bgm.c_str(), DX_PLAYTYPE_LOOP);
	}
}

void ModeMovie::VisibleSkipUI(){
	for (auto&& ui : _ui) {
		if (ui->GetType() == UIBase::Type::SkipUI) {
			static_cast<SkipUI&>(*ui).SetVisibillity(true);
		}
	}
}
