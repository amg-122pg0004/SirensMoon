#pragma once
#include <string>
#include <tchar.h>
#include <vector>

class CharaCodeConvert{
public:
	static std::wstring ConvertUTF8ToWide(const std::string& utf8) ;
	static std::string ConvertWideToMultiByte(const std::wstring& utf16) ;
};
