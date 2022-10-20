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

#include<algorithm>
#include <unordered_map>
#include "NetDataStructs.h"

class InputManager {

public:

	InputManager();//<コンストラクタ
	void InitConfig();

	/**@brief 使用する各キーについてインプット状態を確認して保存 */
	void InputUpdate();
	void InputUpdatePlayer0(int inputType);
	void InputUpdatePlayer0(int key,Vector2 analog);
	void InputUpdatePlayer1(int inputType);
	void InputUpdatePlayer1(int key, Vector2 analog);
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
	std::vector<int> GetPlayer0Key() { return _player0Key; }
	std::vector<int> GetPlayer1Key() { return _player1Key; }
	std::vector<Vector2> GetPlayer0Analog() { return _player0Analog; }
	std::vector<Vector2> GetPlayer1Analog() { return _player1Analog; }
	
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
	// 2進数出力する関数
	std::string ToBin(int a, int keta);
};