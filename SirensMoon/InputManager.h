/*****************************************************************//**
 * \file   InputManager.h
 * \brief	入力状態を取得、保持する
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#pragma once
#include <vector>
#include <string>

class InputManager{

	public:
		
		InputManager();//<コンストラクタ

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
#ifdef _DEBUG
		void Render();
#endif 

		

private:
	/*１キーごとの入力情報*/
	struct KeyInfo {
		std::string ActionName;	//<各ボタンに対応したアクションの名前
		int KeyName;			//<アクションに紐付いているボタンの名前
		bool Hold;				//<入力され続けている間trueを返す
		bool Trigger;			//<入力された瞬間のみtrueを返す
		int PadNo;				//<入力したコントローラーの番号
	};

	/*ゲーム内で使用する各アクションについての入力状態を保存する*/
	std::vector<KeyInfo> KeyState;
};
