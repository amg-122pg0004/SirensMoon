/*****************************************************************//**
 * \file   SoundServer.cpp
 * \brief  音声の読み込み、削除を行うクラスです。
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/
#include "DxLib.h"
#include "SoundServer.h"

std::unordered_map<std::string, int> SoundServer::_mapSounds;

void SoundServer::Init() {
    _mapSounds.clear();
}

void SoundServer::Release() {
    InitSoundMem();
}

void SoundServer::ClearSounds() {
    for (auto&& graph : _mapSounds) {
        DeleteSoundMem(graph.second);
    }
    _mapSounds.clear();
}

int SoundServer::Find(std::string filename)
{
    auto itr = _mapSounds.find(filename);
    if (itr != _mapSounds.end()) {
        return itr->second;
    }
    return -1;
}

int SoundServer::LoadSound(std::string key, std::string filename)
{
    int sound = Find(key);
    if (sound == -1) {
        sound = ::LoadSoundMem(filename.c_str());
        _mapSounds[key] = sound;
    }
    return sound;
}

void SoundServer::StopALLSound(){
    for (auto&& graph : _mapSounds) {
        StopSoundMem(graph.second);
    }
}