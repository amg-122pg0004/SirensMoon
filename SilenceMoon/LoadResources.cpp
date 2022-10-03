#include "LoadResources.h"
#include "ImageServer.h"
#include "SoundServer.h"

LoadResources::LoadResources() {
}
void LoadResources::LoadSE1() {
	SoundServer::LoadSound("DeceideMenu", "resource/SE/UI/DeceideMenu.mp3");
	SoundServer::LoadSound("InputDown", "resource/SE/UI/InputDown.mp3");
	SoundServer::LoadSound("InputUp", "resource/SE/UI/InputUp.mp3");
}

void LoadResources::LoadSE() {

	SoundServer::LoadSound("TakeAmmo", "resource/SE/Gimmick/TakeAmmo.mp3");
	SoundServer::LoadSound("EnterBarrier", "resource/SE/Gimmick/EnterBarrier.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, SoundServer::Find("EnterBarrier"));
	SoundServer::LoadSound("EnterBarrierFail", "resource/SE/Gimmick/EnterBarrierFail.mp3");
	SoundServer::LoadSound("Teleport", "resource/SE/Gimmick/Teleport.mp3");
	SoundServer::LoadSound("ActiveTrapBom", "resource/SE/Gimmick/ActiveTrapBom.mp3");
	SoundServer::LoadSound("AccessSwitch", "resource/SE/Gimmick/AccessSwitch.mp3");
	SoundServer::LoadSound("AccessSwitchEnd", "resource/SE/Gimmick/AccessSwitchEnd.mp3");
	SoundServer::LoadSound("DoorClose", "resource/SE/Gimmick/DoorClose.mp3");
	SoundServer::LoadSound("DoorOpen", "resource/SE/Gimmick/DoorOpen.mp3");
	SoundServer::LoadSound("MicroBomAlarm", "resource/SE/Gimmick/MicroBomAlarm.mp3");
	SoundServer::LoadSound("MicroBomFire", "resource/SE/Gimmick/MicroBomFire.mp3");
	SoundServer::LoadSound("MicroBomRelease", "resource/SE/Gimmick/MicroBomRelease.mp3");
	SoundServer::LoadSound("ScreenBomActive", "resource/SE/Gimmick/ScreenBomActive.mp3");
	SoundServer::LoadSound("ScreenBomRelease", "resource/SE/Gimmick/ScreenBomRelease.mp3");

	SoundServer::LoadSound("PlayerDamage", "resource/SE/Player/Damage.mp3");
	SoundServer::LoadSound("Walking", "resource/SE/Player/Walking.mp3");
	SoundServer::LoadSound("MiniMapClose", "resource/SE/Player/MiniMapClose.mp3");
	SoundServer::LoadSound("MiniMapLooking", "resource/SE/Player/MiniMapLooking.mp3");
	SoundServer::LoadSound("MiniMapOpen", "resource/SE/Player/MiniMapOpen.mp3");
	SoundServer::LoadSound("ServerAccess", "resource/SE/Player/ServerAccess.mp3");
	SoundServer::LoadSound("ServerAccessNow", "resource/SE/Player/ServerAccessNow.mp3");
	SoundServer::LoadSound("ChangeAmmo", "resource/SE/Player/ChangeAmmo.mp3");
	SoundServer::LoadSound("Charging", "resource/SE/Player/Charging.mp3");
	SoundServer::LoadSound("Chargekeep", "resource/SE/Player/Chargekeep.mp3");
	SoundServer::LoadSound("Fire", "resource/SE/Player/Fire.mp3");

	SoundServer::LoadSound("HitBullet", "resource/SE/Bullet/HitBullet.mp3");

	SoundServer::LoadSound("Detection", "resource/SE/Enemy/Detection.mp3");
	ChangeVolumeSoundMem(255 * 100 / 100, SoundServer::Find("Detection"));
}

void LoadResources::LoadEffects() {
	std::vector<int> cg;
	cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/boom2.png", 112, 8, 14, 512, 512, cg.data());
	cg.resize(88);
	ImageServer::LoadDivGraph("resource/Effect/bullethitgreen.png", 88, 8, 11, 128, 128, cg.data());
	ImageServer::LoadDivGraph("resource/Effect/bullethitred.png", 88, 8, 11, 128, 128, cg.data());
	cg.resize(119);
	ImageServer::LoadDivGraph("resource/Effect/chargein.png", 119, 8, 15, 64, 64, cg.data());
	cg.resize(60);
	ImageServer::LoadDivGraph("resource/Effect/chargenow.png", 60, 8, 8, 64, 64, cg.data());

	cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/teleport_inR.png", 68, 4, 17, 128, 128, cg.data());
	cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/teleport_inB.png", 68, 4, 17, 128, 128, cg.data());
	cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/teleport_outR.png", 68, 4, 17, 128, 128, cg.data());
	cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/teleport_outB.png", 68, 4, 17, 128, 128, cg.data());
	cg.resize(117);
	ImageServer::LoadDivGraph("resource/Effect/ScreenSmoke.png", 117, 5, 24, 256, 256, cg.data());
}

void LoadResources::LoadMovie(std::string path) {
	ImageServer::LoadGraph(path);
}

void LoadResources::LoadBossCGs() {
	std::vector<int> handle;
	handle.resize(65);
	ImageServer::LoadDivGraph("resource/Boss/wait.png", 65, 10, 7, 1024, 1024, handle.data());
	handle.resize(40);
	ImageServer::LoadDivGraph("resource/Boss/gunfireA.png", 40, 10, 4, 1024, 1024, handle.data());
	handle.resize(50);
	ImageServer::LoadDivGraph("resource/Boss/gunfireB1.png", 50, 10, 5, 1024, 1024, handle.data());
	ImageServer::LoadDivGraph("resource/Boss/gunfireB2.png", 50, 10, 5, 1024, 1024, handle.data());
	handle.resize(80);
	ImageServer::LoadDivGraph("resource/Boss/missileboss2.png", 80, 10, 8, 840, 740, handle.data());
	handle.resize(70);
	ImageServer::LoadDivGraph("resource/Boss/headbutt.png", 70, 10, 7, 256, 256, handle.data());
	handle.resize(70);
	ImageServer::LoadDivGraph("resource/Boss/jump.png", 70, 10, 7, 1024, 1024, handle.data());
	handle.resize(26);
	ImageServer::LoadDivGraph("resource/Boss/damage.png", 26, 10, 3, 256, 256, handle.data());
	handle.resize(180);
	ImageServer::LoadDivGraph("resource/Boss/thunder2.png", 180, 10, 18, 1024, 740, handle.data());

	handle.resize(120);
	ImageServer::LoadDivGraph("resource/Effect/thunder.png", 120, 8, 15, 200, 150, handle.data());
	handle.resize(16);
	ImageServer::LoadDivGraph("resource/Effect/thunder2.png", 16, 8, 2, 480, 270, handle.data());
	handle.resize(131);
	ImageServer::LoadDivGraph("resource/Effect/fireattack.png", 131, 5, 27, 540, 480, handle.data());
	handle.resize(100);
	ImageServer::LoadDivGraph("resource/Gimmick/Boss/MiniShuttle.png", 100, 5, 20, 570, 1080, handle.data());
	handle.resize(86);
	ImageServer::LoadDivGraph("resource/Gimmick/Boss/MiniShuttle2.png", 86, 5, 18, 570, 540, handle.data());
	handle.resize(70);
	ImageServer::LoadDivGraph("resource/Effect/MissileShoot.png", 70, 7, 12, 220, 340, handle.data());

	SoundServer::LoadSound("Headbutt", "resource/SE/Boss/Headbutt.mp3");
	SoundServer::LoadSound("PreHeadbutt", "resource/SE/Boss/PreHeadbutt.mp3");
	SoundServer::LoadSound("MissileLaunch", "resource/SE/Boss/MissileLaunch.mp3");
	SoundServer::LoadSound("BigRailgunShoot", "resource/SE/Boss/BigRailgunShoot.mp3");
	SoundServer::LoadSound("BigRailgunHit", "resource/SE/Boss/BigRailgunHit.mp3");
	SoundServer::LoadSound("NoDamage", "resource/SE/Boss/NoDamage.mp3");
}