#include "ServerMachineUI.h"
#include <sstream>
#include <fstream>
#include <random>
#include "picojson/picojson.h"
#include "strconv/strconv.h"
#include "Game.h"
#include "ServerMachine.h"
#include "SoundServer.h"
#include "ModeGame.h"
#include "ObjectiveUI.h"

ServerMachineUI::ServerMachineUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }, _visible{ false }, _alpha{ 0 }
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/wanted.png");
	_font = LoadFontDataToHandle("resource/Font/nikkyou-sans-font.ttf", 1);
}

void ServerMachineUI::Update() {
	bool triggerflag{ 0 };
	bool overlapflag{ 0 };
	for (auto&& actor : dynamic_cast<ModeGame&>(_mode).GetObjects()) {
		if (actor->GetType() == Actor::Type::Server) {
			if (dynamic_cast<ServerMachine&>(*actor).GetAccesible()) {
				overlapflag = true;
				if (_game.GetInputManager()->CheckInput("ACCESS", 't', 1)) {
					triggerflag = true;
					SetCGHandle(dynamic_cast<ServerMachine&>(*actor).GetPattern());
				}
			}
		}
	}
	if (!overlapflag) {
		_visible = false;
	}
	if (triggerflag) {
		_visible = !_visible;
	}
	else {

		if (_visible) {
			_alpha += 30;
			if (_alpha > 255) {
				_alpha = 255;
			}
		}
		else {
			_alpha -= 30;
			if (_alpha < 0) {
				_alpha = 0;
			}
		}
	}
	if (_game.GetFrameCount() % 30 == 0) {
		++_animNo;
		if (_animNo >= 8) {
			_animNo = 0;
		}
	}
}

void ServerMachineUI::Render() {
	if (!_visible) {
		return;
	}

	Vector2 chara_posfix{ -200,-80 };
	Vector2 chara_size{ 700,700 };
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);

	DrawBox(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
		static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), GetColor(0, 0, 0), 1);
	DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
		static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), _cg, 1);

	DrawExtendGraph(static_cast<int>(_pos.x + chara_posfix.x),
		static_cast<int>(_pos.y + chara_posfix.y),
		static_cast<int>(_pos.x + chara_posfix.x + chara_size.x),
		static_cast<int>(_pos.y + chara_posfix.y + chara_size.y),
		_cg_bot[_animNo]
		, 1);
	DrawExtendGraph(static_cast<int>(_pos.x + chara_posfix.x),
		static_cast<int>(_pos.y + chara_posfix.y),
		static_cast<int>(_pos.x + chara_posfix.x + chara_size.x),
		static_cast<int>(_pos.y + chara_posfix.y + chara_size.y),
		_cg_top2[_animNo]
		, 1);
	DrawExtendGraph(static_cast<int>(_pos.x + chara_posfix.x),
		static_cast<int>(_pos.y + chara_posfix.y),
		static_cast<int>(_pos.x + chara_posfix.x + chara_size.x),
		static_cast<int>(_pos.y + 600),
		_cg_mid[_animNo]
		, 1);
	DrawExtendGraph(static_cast<int>(_pos.x + chara_posfix.x),
		static_cast<int>(_pos.y + chara_posfix.y),
		static_cast<int>(_pos.x + chara_posfix.x + chara_size.x),
		static_cast<int>(_pos.y + chara_posfix.y + chara_size.y),
		_cg_top[_animNo]
		, 1);

	/*説明文出力*/
	Vector2 text_posfix{ 300,225 };
	std::stringstream ss;
	ss << _message[0] << "\n";
	ss << _message[1] << "\n";
	ss << _message[2] << "\n";
	DrawStringToHandle(static_cast<int>(_pos.x + text_posfix.x), static_cast<int>(_pos.y + text_posfix.y),
		ss.str().c_str(), GetColor(255, 255, 255), _font);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ServerMachineUI::SetCGHandle(EnemyGenerator::EnemyPattern pattern) {
	LoadMessage(pattern);
	std::string head2path{ "resource/Enemy/2_head" };
	switch (pattern.head) {
	case 1:
	case 3:
	case 7:
	case 8:
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		break;
	case 2:
	case 4:
	case 5:
	case 6:
	case 9:
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/2.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/3.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/4.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/6.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/7.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/8.png"));
		break;
	}
	std::string headpath{ "resource/Enemy/head" };
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/1.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/2.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/3.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/4.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/5.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/6.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/7.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/8.png"));
	std::string bodypath{ "resource/Enemy/body" };
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/1.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/2.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/3.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/4.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/5.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/6.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/7.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/8.png"));
	std::string footpath{ "resource/Enemy/foot" };
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/1.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/2.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/3.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/4.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/5.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/6.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/7.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/8.png"));
}

void ServerMachineUI::LoadMessage(EnemyGenerator::EnemyPattern pattern) {
	// ファイルからjsonデータの読み込み
	std::ifstream ifs("resource/Enemy/Text/tips.json");
	picojson::value json;
	ifs >> json;
	// jsonデータからパラメータを取得
	picojson::object jsRoot = json.get<picojson::object>();

	std::string message1 = jsRoot["head" + std::to_string(pattern.head)].get<std::string>();
	std::wstring w_ss = utf8_to_wide(message1);
	_message.push_back(wide_to_sjis(w_ss));

	std::string message2 = jsRoot["body" + std::to_string(pattern.body)].get<std::string>();
	std::wstring w_ss2 = utf8_to_wide(message2);
	_message.push_back(wide_to_sjis(w_ss2));

	std::string message3 = jsRoot["foot" + std::to_string(pattern.foot)].get<std::string>();
	std::wstring w_ss3 = utf8_to_wide(message3);
	_message.push_back(wide_to_sjis(w_ss3));

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(_message.begin(), _message.end(), engine);

}
