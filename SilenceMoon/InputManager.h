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

class InputManager{

	public:

		InputManager();//<コンストラクタ
		void Init();//<コントローラー設定の初期化


		/**@brief 使用する各キーについてインプット状態を確認して保存 */
		void InputUpdate();
		
		/**
		* @brief 特定のキーの入力状態を確認する
		*
		* \param actionname 確認したいキーアクションの名前
		* \param keystate 確認したいキーの状態 'h'で押し続けているか？'t'で押した瞬間か？
		* \return 入力があればtrue
		*/
		bool CheckInput(const std::string actionname,const char keystate,int playernum);

		/**
		* @brief アナログスティックの入力状態を確認する
		*
		* \param playernum 何個目のコントローラーか
		* \return 入力状態をそのまま返す
		*/
		Vector2 CheckAnalogInput(const int playernum);

		void ChangeControllerNo();

#ifdef _DEBUG
		void Render();
#endif 

		/*１キーごとの入力情報*/
		struct KeyInfo {
			std::string ActionName;	//<各ボタンに対応したアクションの名前
			int KeyName;			//<アクションに紐付いているボタンの名前
			bool Hold;				//<入力され続けている間trueを返す
			bool Trigger;			//<入力された瞬間のみtrueを返す
			bool Release;			//入力が無くなった瞬間のみtrueを返す
			int PadNo;				//<入力したコントローラーの番号
		};
		struct AnalogInfo {
			Vector2 Value;
			int PadNo;
		};
		std::vector<KeyInfo> GetKeyState() { return _keyState; }
		std::vector<AnalogInfo> GetAnalogState() { return _analogState; }
private:

	/*ゲーム内で使用する各アクションについての入力状態を保存する*/
	std::vector<KeyInfo> _keyState;
	
	/*アナログスティックの入力情報*/
	std::vector<AnalogInfo> _analogState;

	/*コントローラーを入れ替えるフラグ*/
	bool _changeFlag;

	/*接続中のコントローラーの数*/
	int _connectNumber;
};