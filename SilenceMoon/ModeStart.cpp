#include "ModeStart.h"
#include "Game.h"
#include "ModeGame.h"
#include "SkipUI.h"
#include "Screen_Fade.h"

ModeStart::ModeStart(Game& game,int seekmovie) :ModeBase(game), _select{ 0 }, _alpha{ 255 }, _pos{ 440 , 730 }, _bgm{ false }
{
	_inputManager = _game.GetInputManager();
	_font = CreateFontToHandle("OPTION",52,10, DX_FONTTYPE_EDGE);
	LoadResources::LoadSE1();
	LoadResources::LoadEffects();
	LoadResources::LoadMovie("resource/Movie/gameover.mp4");
	_movieHandle = ImageServer::LoadGraph("resource/Movie/start.mp4");
	_cg_bg = ImageServer::LoadGraph("resource/UI/Start/background.jpg");
	_cg_logo = ImageServer::LoadGraph("resource/UI/Start/logo.png");
	_cg_cursor = ImageServer::LoadGraph("resource/UI/Start/cursor.png");
	_cg_start.first = ImageServer::LoadGraph("resource/UI/Start/start_passive.png");
	_cg_start.second = ImageServer::LoadGraph("resource/UI/Start/start_active.png");
	_cg_quit.first = ImageServer::LoadGraph("resource/UI/Start/quit_passive.png");
	_cg_quit.second = ImageServer::LoadGraph("resource/UI/Start/quit_active.png");
	_cg_credit.first = ImageServer::LoadGraph("resource/UI/Start/credit_passive.png");
	_cg_credit.second = ImageServer::LoadGraph("resource/UI/Start/credit_active.png");
	_cg2pFrame = ImageServer::LoadGraph("resource/UI/Start/2p_frame.png");
	_cg2pText = ImageServer::LoadGraph("resource/UI/Start/2p_text.png");
	SeekMovieToGraph(_movieHandle, seekmovie);
	PlayMovieToGraph(_movieHandle);
	Vector2 pos{ 800,0 }, size{ 163,163 };
	_ui.emplace_back(std::make_unique<SkipUI>(_game, *this,*_splitWindow, pos, size));
	VisibleSkipUI();
}

void ModeStart::Update() {
	ModeBase::Update();
	_loadingNumber = GetASyncLoadNum();
	if (_loadingNumber == 0 && GetJoypadInputState(DX_INPUT_KEY_PAD1) && !_game.GetInputManager()->CheckInput("PAUSE", 't', 0) ||
		_loadingNumber == 0 && GetJoypadInputState(DX_INPUT_PAD2) && !_game.GetInputManager()->CheckInput("PAUSE", 't', 1)) {
		if (GetMovieStateToGraph(_movieHandle) ==1) {
			VisibleSkipUI();
		}
	}
	auto analog1 = _inputManager->CheckAnalogInput(0);
	if (_pos.y <= 540) {
		if (abs(analog1.y) > 800) {
			if (!_analogFlag1) {
				_analogFlag1 = true;
				if (analog1.y > 0) {
					++_select;
					PlaySoundMem(SoundServer::Find("InputDown"), DX_PLAYTYPE_BACK);
					if (_select > 3) {
						_select = 0;
					}
				}
				else {
					PlaySoundMem(SoundServer::Find("InputUp"), DX_PLAYTYPE_BACK);
					--_select;
					if (_select < 0) {
						_select = 3;
					}
				}
			}
		}

		if (abs(analog1.y) < 50) {
			_analogFlag1 = false;
		}

		if (_inputManager->CheckInput("ACCESS", 't', 0)) {
			PlaySoundMem(SoundServer::Find("DeceideMenu"), DX_PLAYTYPE_BACK);
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
			case 3:
				NetWork();
				break;
			default:
				break;
			}
		}
	}
	for (auto&& ui : _ui) {
		ui->Update();
	}
}

void ModeStart::Render() {
	ClearDrawScreen();
	if (GetMovieStateToGraph(_movieHandle) == 1 && TellMovieToGraph(_movieHandle) > 125000) {
		PauseMovieToGraph(_movieHandle);
		for (auto&& ui : _ui) {
			if (ui->GetType() == UIBase::Type::SkipUI) {
				static_cast<SkipUI&>(*ui).SetVisibillity(false);
			}
		}
	}
	if (GetMovieStateToGraph(_movieHandle) == 1 && _inputManager->CheckInput("PAUSE", 't', 0) ||
		GetMovieStateToGraph(_movieHandle) == 1 && _inputManager->CheckInput("PAUSE", 't', 1)) {
		if (!_bgm) {
			PlaySoundFile("resource/BGM/title.mp3", DX_PLAYTYPE_LOOP);
			_bgm = true;
		}
		PauseMovieToGraph(_movieHandle);
		for (auto&& ui : _ui) {
			if (ui->GetType() == UIBase::Type::SkipUI) {
				static_cast<SkipUI&>(*ui).SetVisibillity(false);
			}
		}
	}
	if (GetMovieStateToGraph(_movieHandle) == 1 && TellMovieToGraph(_movieHandle) > 124000) {
		if (!_bgm) {
			PlaySoundFile("resource/BGM/title.mp3", DX_PLAYTYPE_LOOP);
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

		//座標469 742　縮小率 68%
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
			if (_select == 3) {
				DrawBox(static_cast<int>(pos2.x)+70, static_cast<int>(pos2.y) + 300, static_cast<int>(pos2.x) + 290, static_cast<int>(pos2.y) + 300 + 50,
					GetColor(255, 255, 255), false);
			}
			DrawStringToHandle(static_cast<int>(pos2.x)+80, static_cast<int>(pos2.y) + 300, "NETWORK",GetColor(255,255,255),_font);
			DrawGraph(static_cast<int>(pos2.x - 50), static_cast<int>(pos2.y) + _select * 100, _cg_cursor, 1);
			DrawGraph(static_cast<int>(pos2.x + screen_W / 2)-100, static_cast<int>(pos2.y)+100, _cg2pFrame, 1);
			int alpha = static_cast<int>((sin(static_cast<double>(_game.GetFrameCount() / 15.0)) / 2.0 + 0.7) * 255.0);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha));
			DrawGraph(static_cast<int>(pos2.x + screen_W / 2)-100, static_cast<int>(pos2.y)+100, _cg2pText, 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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
		DrawRotaGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			0.635, 0, _cg_logo, 1, 0);
		DrawRotaGraph(static_cast<int>(_pos.x + screen_W - splitscreen_W), static_cast<int>(_pos.y),
			0.635, 0, _cg_logo, 1, 0);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	for (auto&& ui : _ui) {
		ui->Render();
	}
}

void ModeStart::Debug() {

}

void ModeStart::Play() {
	Vector2 pos{ 0,0 }, size{ screen_W,screen_W };
	auto fade = std::make_unique<Screen_Fade>(_game, *this, *_splitWindow, pos, size);
	fade->SetEffect(0,10,GetColor(0,0,0),false,true);
	_ui.push_back(std::move(fade));
	ModeBase::NextMode(11);
}

void ModeStart::Credit() {
	_game.PlayCredit();
}

void ModeStart::Quit() {
	DxLib_End();
}

void ModeStart::NetWork() {
	
}

void ModeStart::VisibleSkipUI() {
	for (auto&& ui : _ui) {
		if (ui->GetType() == UIBase::Type::SkipUI) {
			static_cast<SkipUI&>(*ui).SetVisibillity(true);
		}
	}
}