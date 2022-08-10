#include "GameOverUI.h"
#include "ImageServer.h"
#include "Game.h"
#include "ModeGameOver.h"

GameOverUI::GameOverUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
:UIBase(game,mode,pos,size)
{
	_cg = ImageServer::LoadGraph("resource/UI/gameover.png");
	_startTime = game.GetFrameCount();

	_easing = Easing::GetMode("Linear");
}

void GameOverUI::Update() {
	auto elapsed = _game.GetFrameCount() - _startTime; // �o�ߎ���
	auto start = 0;    // �J�n�l
	auto stop = 255;        // �I���l
	auto lifetime = 60 * 2; // ��������

	if (elapsed < lifetime*2) {
		// �����_���̃C�[�W���O�֐����g��
		_alpha = _easing(elapsed, start, stop, lifetime);
	}
	else {
		dynamic_cast<ModeGameOver&>(_mode).RestartGame();
	}

}

void GameOverUI::Render() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha-100));
	
	DrawBox(0,0,screen_W,screen_H,GetColor(0,0,0),1);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));

	DrawGraph(0,0,_cg,1);
	DrawGraph(splitscreen_W+60, 0, _cg, 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
