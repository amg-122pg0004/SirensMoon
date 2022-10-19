/*****************************************************************//**
 * \file   InputManager.h
 * \brief	入力状態を取得、保持する
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#pragma once
#include "Math.h"
#include <vector>
#include <string>
#include <array>
#include <unordered_map>

class InputManager {

public:

	InputManager();//<コンストラクタ
	void InitConfig();

	/**@brief 使用する各キーについてインプット状態を確認して保存 */
	void InputUpdate();
	void InputUpdatePlayer0(int inputType);
	void InputUpdatePlayer1(int inputType);
	/**
	* @brief 特定のキーの入力状態を確認する
	*
	* \param actionname 確認したいキーアクションの名前
	* \param keystate 確認したいキーの状態 'h'で押し続けているか？'t'で押した瞬間か？
	* \return 入力があればtrue
	*/
	bool CheckInput(const std::string actionname, const char keystate, int playernum);

	/**
	* @brief アナログスティックの入力状態を確認する
	*
	* \param playernum 何個目のコントローラーか
	* \return 入力状態をそのまま返す
	*/
	Vector2 CheckAnalogInput(const int playernum);

	void ChangeControllerNo();
	void SetOnline(int playerNo) { _online = playerNo; }

#ifdef _DEBUG
	void Render();
#endif 
	//std::vector<KeyInfo> GetKeyState() { return _keyState; }
	//std::vector<AnalogInfo> GetAnalogState() { return _analogState; }

	void SetUDPData(std::array<int, 14> rawData);
	int GetOnlinePlayer() { return _online; };
private:
	/*キー対応設定*/
	std::unordered_map<std::string, int> _player0Config, _player1Config;
	/*キーの入力状態を過去フレーム含めて保存（最新はback()）*/
	std::vector<int> _player0Key, _player1Key;
	/*アナログスティックの入力状態を過去フレーム含めて保存最新はback())*/
	std::vector<Vector2> _player0Analog, _player1Analog;

	/*コントローラーを入れ替えるフラグ*/
	bool _changeFlag;

	/*接続中のコントローラーの数*/
	int _connectNumber;

	int _online;
};