/*****************************************************************//**
 * \file   WinMain.cpp
 * \brief  �v���O�����̃G���g���[�|�C���g
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#include <DxLib.h>
#include "Game.h"
#include <memory>

int WINAPI WinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    ChangeWindowMode(TRUE);    //<�E�C���h�E���[�h�ɕύX
    SetGraphMode(screen_W, screen_H, screen_Depth);    //<��ʂ̉𑜓x(��,����)�ƐF��(32bit)���w��
    DxLib_Init();    //<Dx���C�u����������
    SetDrawScreen(DX_SCREEN_BACK);    //<�`����ʂ𗠂ɂ���

    auto game = std::make_unique<Game>();

    /*���C�����[�v*/
    while (ProcessMessage() != -1) {

        /*ESC����������Q�[���I��**/
        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }

        game->Input();
        game->Update();
        game->Render();
        game->Debug();
        ScreenFlip();
    }

    DxLib_End();

    return 0;
}