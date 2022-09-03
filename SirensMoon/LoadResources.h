#pragma once
#include <DxLib.h>
#include <vector>
#include <string>

class LoadResources{
public:
	LoadResources();
	static void LoadSE1();
	static void LoadSE();
	static void LoadEffects();
	static void LoadMovie(std::string path);
};
