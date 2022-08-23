/*****************************************************************//**
 * \file   WinMain.cpp
 * \brief  プログラムのエントリーポイント
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#include <DxLib.h>
#include "Game.h"
#include <memory>

int WINAPI WinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    ChangeWindowMode(TRUE);    //<ウインドウモードに変更
    SetGraphMode(screen_W, screen_H, screen_Depth);    //<画面の解像度(幅,高さ)と色数(32bit)を指定
    DxLib_Init();    //<Dxライブラリ初期化
    SetDrawScreen(DX_SCREEN_BACK);    //<描画先画面を裏にする

    auto game = std::make_unique<Game>();

    /*メインループ*/
    while (ProcessMessage() != -1) {

        /*ESCを押したらゲーム終了**/
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