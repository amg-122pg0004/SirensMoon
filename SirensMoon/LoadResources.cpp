#include "LoadResources.h"
#include "ImageServer.h"
#include "SoundServer.h"

LoadResources::LoadResources() {
}

void LoadResources::LoadSE() {
	SoundServer::LoadSound("PlayerWalk", "resource/Sounds/Player/se_sk2206.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerWalk"));
	SoundServer::LoadSound("PlayerRun", "resource/Sounds/Player/se_sk2207.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerRun"));
	SoundServer::LoadSound("PlayerAim", "resource/Sounds/Player/se_sk2054.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerAim"));
	SoundServer::LoadSound("PlayerCharge", "resource/Sounds/Player/se_sk2153.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerCharge"));
	SoundServer::LoadSound("PlayerShoot", "resource/Sounds/Player/se_sk2177.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerShoot"));
	SoundServer::LoadSound("PlayerChargeMAX", "resource/Sounds/Player/se_sk2224.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerChargeMAX"));
	SoundServer::LoadSound("BulletToWall", "resource/Sounds/Player/se_sk2026.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("BulletToWall"));
	SoundServer::LoadSound("BulletToEnemy", "resource/Sounds/Player/se_sk2020.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("BulletToEnemy"));
	SoundServer::LoadSound("PlayerOpenMap", "resource/Sounds/Player/se_sk2050.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerOpenMap"));
	SoundServer::LoadSound("Explosion", "resource/Sounds/Gimmick/se_sk2063.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("PlayerOpenMap"));
	SoundServer::LoadSound("DamageToPlayer", "resource/Sounds/Enemy/se_sk2077.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("DamageToPlayer"));
}

void LoadResources::LoadEffects() {
	std::vector<int> cg;
	cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/boom2.png", 112, 8, 14, 512, 512, cg.data());
	cg.resize(88);
	ImageServer::LoadDivGraph("resource/Effect/bullethitgreen.png", 88, 8, 11, 512, 512, cg.data());
	ImageServer::LoadDivGraph("resource/Effect/bullethitred.png", 88, 8, 11, 512, 512, cg.data());
	cg.resize(119);
	ImageServer::LoadDivGraph("resource/Effect/chargein.png", 119, 8, 15, 512, 512, cg.data());
	cg.resize(60);
	ImageServer::LoadDivGraph("resource/Effect/chargenow.png", 60, 8, 8, 512, 512, cg.data());
}

void LoadResources::LoadMovie(std::string path){
	ImageServer::LoadGraph(path);
}
