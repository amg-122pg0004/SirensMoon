#include "ModeStart.h"
#include "Game.h"
#include "ModeGame.h"

ModeStart::ModeStart(Game& game) :ModeBase(game),_select{0},_alpha{255}, _pos{ 440 , 730 },_bgm{false}
{
	_inputManager = _game.GetInputManager();

	_movieHandle = ImageServer::LoadGraph("resource/Movie/start.mp4");
	_cg_bg=ImageServer::LoadGraph("resource/UI/Start/background.jpg");
	_cg_logo = ImageServer::LoadGraph("resource/UI/Start/logo.png");
	_cg_cursor = ImageServer::LoadGraph("resource/UI/Start/cursor.png");
	_cg_start.first = ImageServer::LoadGraph("resource/UI/Start/start_passive.png");
	_cg_start.second = ImageServer::LoadGraph("resource/UI/Start/start_active.png");
	_cg_quit.first = ImageServer::LoadGraph("resource/UI/Start/quit_passive.png");
	_cg_quit.second = ImageServer::LoadGraph("resource/UI/Start/quit_active.png");
	_cg_credit.first = ImageServer::LoadGraph("resource/UI/Start/credit_passive.png");
	_cg_credit.second = ImageServer::LoadGraph("resource/UI/Start/credit_active.png");
	PlayMovieToGraph(_movieHandle);
	//SeekMovieToGraph(_movieHandle,120000);//<爆破シーンまでスキップ
}

void ModeStart::Update() {
	auto analog1 = _inputManager->CheckAnalogInput(0);
	if (_pos.y <= 540) {
		if (abs(analog1.y) > 800) {
			if (!_analogFlag1) {
				_analogFlag1 = true;
				if (analog1.y > 0) {
					++_select;
					if (_select > 2) {
						_select = 0;
					}
				}
				else {
					--_select;
					if (_select < 0) {
						_select = 2;
					}
				}
			}
		}
		if (abs(analog1.y) < 50) {
			_analogFlag1 = false;
		}
		if (_inputManager->CheckInput("ACCESS", 't', 0)) {
			switch (_select)
			{
			case 0:
				Play();
				break;
			case 1:
				Credit();
				break;
			case 2:
				Quit();
				break;
			default:
				break;
			}
		}
	}
}

void ModeStart::Render() {
	ClearDrawScreen();
	if (GetMovieStateToGraph(_movieHandle) == 1&&TellMovieToGraph(_movieHandle) > 128000) {
		PauseMovieToGraph(_movieHandle);
	}
	if (GetMovieStateToGraph(_movieHandle) == 1 && _inputManager->CheckInput("PAUSE", 't', 0)) {
		if (!_bgm) {
			PlaySoundFile("resource/BGM/title.wav", DX_PLAYTYPE_LOOP);
			_bgm = true;
		}
		PauseMovieToGraph(_movieHandle);
	}
	if (GetMovieStateToGraph(_movieHandle) == 1 && TellMovieToGraph(_movieHandle) > 126500) {
		if (!_bgm) {
			PlaySoundFile("resource/BGM/title.wav", DX_PLAYTYPE_LOOP);
			_bgm = true;
		}
	}
	if (GetMovieStateToGraph(_movieHandle) == 1) {
		DrawGraph(0, 36, _movieHandle, 0);
		DrawGraph(screen_W - splitscreen_W, 36, _movieHandle, 0);
	}
	else if (GetMovieStateToGraph(_movieHandle) == 1) {
		Vector2 size{ 1280,720 };
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), static_cast<int>(_pos.x + size.x), static_cast<int>(_pos.y + size.y), _cg_logo, 1);
		DrawExtendGraph(static_cast<int>(_pos.x) + splitscreen_W,
			static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + splitscreen_W + size.x),
			static_cast<int>(_pos.y + size.y), _cg_logo, 1);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		DrawGraph(0, 0, _cg_bg, 0);
		Vector2 pos2{ splitscreen_W / 2 - 180,screen_H / 2 + 50 };

		//座標469 742　縮小率 68%　 あせもあり
		/*選択位置を参照して画像を切り返る関数*/
		auto select = [this](std::pair<int, int> cg, int index) {
			if (_select == index) {
				return cg.second;
			}
			else {
				return cg.first;
			}; };

		_pos.y -= 2;
		if (_pos.y < 540) {
			_pos.y = 540;
			DrawGraph(static_cast<int>(pos2.x), static_cast<int>(pos2.y), select(_cg_start, 0), 1);
			DrawGraph(static_cast<int>(pos2.x), static_cast<int>(pos2.y) + 100, select(_cg_credit, 1), 1);
			DrawGraph(static_cast<int>(pos2.x), static_cast<int>(pos2.y) + 200, select(_cg_quit, 2), 1);
			DrawGraph(static_cast<int>(pos2.x - 50), static_cast<int>(pos2.y) + _select * 100, _cg_cursor, 1);
		}

		/*フェードイン用の黒BOX描画*/
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
		DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		_alpha -= 5;
	}
	if (GetMovieStateToGraph(_movieHandle) != 1) {

		Vector2 size{ 1280,720 };
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(static_cast<int>(_pos.x),static_cast<int>(_pos.y),
			0.635 , 0, _cg_logo, 1 , 0 );
		DrawRotaGraph(static_cast<int>(_pos.x +screen_W - splitscreen_W),static_cast<int>(_pos.y),
			0.635 , 0, _cg_logo, 1 , 0 );
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}

void ModeStart::Debug(){

}

void ModeStart::Play() {
	StopSoundFile();
	_game.GetModeServer()->Clear();
	auto mode = std::make_unique<ModeGame>(_game);
	_game.GetModeServer()->Add(std::move(mode));
}

void ModeStart::Credit() {

}

void ModeStart::Quit(){
	DxLib_End();
}