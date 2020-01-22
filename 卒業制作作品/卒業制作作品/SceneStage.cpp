#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//�g�p����GameL�w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"
#include"GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include <time.h>

#include "GameHead.h"
#include "SceneStage.h"

//�R���X�g���N�^
CSceneStage::CSceneStage()
{

}

//�e�X�g���N�^
CSceneStage::~CSceneStage()
{

}

//���������\�b�h
void CSceneStage::InitScene()
{
	//Font�쐬
	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"�X�e�[�W.png", 0, TEX_SIZE_512);
	Draw::LoadImage(L"�e�e�܂Ƃ�.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"���̒r.png", 3, TEX_SIZE_512);
	Draw::LoadImage(L"�G�l�~�[�܂Ƃ�.png", 4, TEX_SIZE_512);
	Draw::LoadImage(L"��.png", 5, TEX_SIZE_512);
	Draw::LoadImage(L"���u�E�ݒu��.png", 6, TEX_SIZE_512);
	Draw::LoadImage(L"�A�C�e���E�ݒu��.png", 7, TEX_SIZE_512);
	Draw::LoadImage(L"���m�E�R�l.png", 8, TEX_SIZE_512);
	Draw::LoadImage(L"����.png", 9, TEX_SIZE_512);
	Draw::LoadImage(L"�����Ԃ��A�j���[�V����.png", 10, TEX_SIZE_512);
	Draw::LoadImage(L"����\���p.png", 11, TEX_SIZE_512);
	Draw::LoadImage(L"�Ə�.png", 12, TEX_SIZE_512);
	Draw::LoadImage(L"�@�ށE����.png", 29, TEX_SIZE_512);
	Draw::LoadImage(L"image.png", 30, TEX_SIZE_512);
	Draw::LoadImage(L"image2.png", 31, TEX_SIZE_512);
	Draw::LoadImage(L"image3.png", 32, TEX_SIZE_512);
	Draw::LoadImage(L"�������.png", 33, TEX_SIZE_1024);

	//���y���ǂݍ��� 
	Audio::LoadAudio(0, L"�X�e�[�WBGM.wav", SOUND_TYPE::BACK_MUSIC);
	//���y���̓ǂݍ���
	Audio::LoadAudio(1, L"�I����.wav", EFFECT);
	Audio::LoadAudio(2, L"���艹.wav", EFFECT);
	Audio::LoadAudio(3, L"�n���h�K���e��.wav", EFFECT);
	Audio::LoadAudio(4, L"�V���b�g�K���e��.wav", EFFECT);
	Audio::LoadAudio(5, L"�X�i�C�p�[���C�t���e��.wav", EFFECT);
	Audio::LoadAudio(6, L"���P�b�g�����`���[.wav", EFFECT);
	Audio::LoadAudio(7, L"���[���K��.wav", EFFECT);
	Audio::LoadAudio(8, L"�A�C�e����[��.wav", EFFECT);
	Audio::LoadAudio(9, L"������.wav", EFFECT);
	Audio::LoadAudio(10, L"�e�؂�.wav", EFFECT);
	Audio::LoadAudio(11, L"�]���r1.wav", EFFECT);
	Audio::LoadAudio(12, L"�A�C�e���l����.wav", EFFECT);
	Audio::LoadAudio(13, L"�����[�h��.wav", EFFECT);
	Audio::LoadAudio(14, L"�_���[�W��.wav", EFFECT);
	Audio::LoadAudio(15, L"�����Ԃ���.wav", EFFECT);
	Audio::LoadAudio(16, L"�x����.wav", EFFECT);
	Audio::LoadAudio(17, L"�C�x���g���s��.wav", EFFECT);
	Audio::LoadAudio(19, L"�N����.wav", EFFECT);
	Audio::LoadAudio(20, L"�H�΂�����.wav", EFFECT);
	Audio::LoadAudio(21, L"�J�E���g�_�E��.wav", EFFECT);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	Audio::Start(0); //���y�X�^�[�g

	//��l���@�I�u�W�F�N�g�쐬
	CObjHero* obj_h = new CObjHero(368.0f, 268.0f);
	Objs::InsertObj(obj_h, OBJ_HERO, 8);

	//�Ə��I�u�W�F�N�g�쐬
	CObjAiming* obj_ai = new CObjAiming();
	Objs::InsertObj(obj_ai, OBJ_AIMING, 12);

	//�w�i�I�u�W�F�N�g�쐬
	C0bjBackground * back = new C0bjBackground();
	Objs::InsertObj(back, OBJ_BACKGROUND, 1);

	//�{�X�I�u�W�F�N�g�쐬 
	CObjBoss*obj_boss = new CObjBoss(272, 350);
	Objs::InsertObj(obj_boss, OBJ_BOSS, 2);	

	//���d�@�I�u�W�F�N�g�쐬	
	CObjGenerator* Gen = new CObjGenerator(-300, -400);
	Objs::InsertObj(Gen, OBJ_GENERATOR, 2);

	CObjGenerator2* Gen2 = new CObjGenerator2(1100, 900);
	Objs::InsertObj(Gen2, OBJ_GENERATOR2, 2);

	//�G���͉����u�I�u�W�F�N�g�쐬
	CObjEnemy_Neutralization_Device* END = new CObjEnemy_Neutralization_Device(1100, -400);
	Objs::InsertObj(END, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 2);

	CObjEnemy_Neutralization_Device2* END2 = new CObjEnemy_Neutralization_Device2(-300, 900);
	Objs::InsertObj(END2, OBJ_ENEMY_NEUTRALIZATION_DEVICE2, 2);

	//�~�[�����Ԗ��͉����u�I�u�W�F�N�g�쐬
	CObjMeme_Neutralization_Device* MND = new CObjMeme_Neutralization_Device(375, -500);
	Objs::InsertObj(MND, OBJ_MEME_NEUTRALIZATION_DEVICE, 2);

	//�L�h�S���I�u�W�F�N�g�쐬 x=202 y=72(��)
	CObjBarbedWire* Barbed;
	//����
	for (int x = -402; x < 0; x += 202)
	{
		Barbed = new CObjBarbedWire(x, -300);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	for (int x = -400; x < -103; x += 101)
	{
		Barbed = new CObjBarbedWire(x, -500);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	//����
	for (int x = -425; x < -23; x += 202)
	{
		Barbed = new CObjBarbedWire(x, 800);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	for (int x = -427; x < -130; x += 101)
	{
		Barbed = new CObjBarbedWire(x, 1000);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	//�E��
	for (int x = 973; x < 1375; x += 202)
	{
		Barbed = new CObjBarbedWire(x, -300);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	for (int x = 975; x < 1278; x += 101)
	{
		Barbed = new CObjBarbedWire(x, -500);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	//�E��
	for (int x = 998; x < 1400; x += 202)
	{
		Barbed = new CObjBarbedWire(x, 800);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	for (int x = 1000; x < 1303; x += 101)
	{
		Barbed = new CObjBarbedWire(x, 1000);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}

	//�L�h�S���I�u�W�F�N�g�쐬 x=72 y=202(�c)
	CObjBarbedWireV* BarbedV;
	//����
	BarbedV = new CObjBarbedWireV(-400, -430, false);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	BarbedV = new CObjBarbedWireV(-170, -430, true);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	//����
	BarbedV = new CObjBarbedWireV(-425, 872, false);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	BarbedV = new CObjBarbedWireV(-195, 872, true);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	//�E��
	BarbedV = new CObjBarbedWireV(975, -430, false);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	BarbedV = new CObjBarbedWireV(1207, -430, true);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);	
	//�E��
	BarbedV = new CObjBarbedWireV(998, 872, false);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	BarbedV = new CObjBarbedWireV(1229, 872, true);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	

	//�L�h�S��(�~�j)�I�u�W�F�N�g�쐬 x=68 y=53
	CObjBarbedWireSmall* BarbedS;
	//��
	for (int x = 302; x < 504; x += 68)
	{
		BarbedS = new CObjBarbedWireSmall(x, -225);
		Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 3);
	}
	//��
	for (int x = 302; x < 504; x += 68)
	{
		BarbedS = new CObjBarbedWireSmall(x, 800);
		Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 3);
	}

	//�ԃI�u�W�F�N�g�쐬(��) x=202 y=72
	CObjNet* Net = new CObjNet(0, 0);
	//��---------------------------------------
	//����
	for (int x = -602; x < 206; x += 202)
	{
		Net = new CObjNet(x, -100);
		Objs::InsertObj(Net, OBJ_NET, 3);
	}
	//����
	for (int x = -602; x < 206; x += 202)
	{
		Net = new CObjNet(x, 650);
		Objs::InsertObj(Net, OBJ_NET, 3);
	}
	//�E��
	for (int x = 602; x < 1408; x += 202)
	{
		Net = new CObjNet(x, -100);
		Objs::InsertObj(Net, OBJ_NET, 3);
	}
	//�E��
	for (int x = 602; x < 1408; x += 202)
	{
		Net = new CObjNet(x, 650);
		Objs::InsertObj(Net, OBJ_NET, 3);
	}
	//------------------------------------------

	//�ԃI�u�W�F�N�g�쐬(�c) x=72 y=202
	CObjNetV* NetV = new CObjNetV(800, 200);
	//�c----------------------------------------
	//����
	for (int y = -302; y < -100; y += 202)
	{
		NetV = new CObjNetV(134, y);
		Objs::InsertObj(NetV, OBJ_NET, 3);
	}
	//����
	for (int y = 722; y < 924; y += 202)
	{
		NetV = new CObjNetV(134, y);
		Objs::InsertObj(NetV, OBJ_NET, 3);
	}
	//�E��
	for (int y = -302; y < -100; y += 202)
	{
		NetV = new CObjNetV(602, y);
		Objs::InsertObj(NetV, OBJ_NET, 3);
	}
	//�E��
	for (int y = 722; y < 924; y += 202)
	{
		NetV = new CObjNetV(602, y);
		Objs::InsertObj(NetV, OBJ_NET, 3);
	}
	//------------------------------------------
	
	//�A�C�e���I�u�W�F�N�g�쐬	
	//���P�b�g�����`���[�e��[
	CObjRocketLauncherItem* RLi = new CObjRocketLauncherItem(50, -150);
	Objs::InsertObj(RLi, OBJ_ROCKETLAUNCHER_ITEM, 4);
	//���[���K���e��[
	CObjRailGunItem* RGi = new CObjRailGunItem(700, -150);
	Objs::InsertObj(RGi, OBJ_RAILGUN_ITEM, 4);
	//�O���l�[�h��[
	CObjGrenadeItem* GREi = new CObjGrenadeItem(70, 730);
	Objs::InsertObj(GREi, OBJ_GRENADE_ITEM, 4);
	//��
	CObjHeal* Heal = new CObjHeal(700, 730);
	Objs::InsertObj(Heal, OBJ_HEAL, 4);
	//�A�[�}�[
	CObjArmor* Armor = new CObjArmor(381.0f, 150.0f);
	Objs::InsertObj(Armor, OBJ_ARMOR, 4);
	

	//�A�C�e���h���b�v�I�u�W�F�N�g�쐬	
	CObjAitemDrop* obj_ad = new CObjAitemDrop();
	Objs::InsertObj(obj_ad, OBJ_AITEMDROP, 8);

	//�ݒu�^�V���b�g�K���e��[
	CObjInstallation_Type_ShotGun* obj_it_shg = new CObjInstallation_Type_ShotGun(-300, -640);
	Objs::InsertObj(obj_it_shg, OBJ_INSTALL_TYPE_SHG, 8);
	//�ݒu�^�A�T���g���C�t���e��[
	CObjInstallation_Type_AR* obj_it_ar = new CObjInstallation_Type_AR(1075, -640);
	Objs::InsertObj(obj_it_ar, OBJ_INSTALL_TYPE_AR, 8);
	//�ݒu�^�X�i�C�p�[���C�t���e��[
	CObjInstallation_Type_SR* obj_it_sr = new CObjInstallation_Type_SR(-293, 670);
	Objs::InsertObj(obj_it_sr, OBJ_INSTALL_TYPE_SR, 8);
	//�ݒu�^�����_���A�C�e���{�b�N�X
	CObjInstallation_Type_RandBox* obj_it_rb = new CObjInstallation_Type_RandBox(1130, 720);
	Objs::InsertObj(obj_it_rb, OBJ_INSTALL_TYPE_RANDBOX, 8);

	//�ǃI�u�W�F�N�g�쐬
	//��
	CObjWall* Wall = new CObjWall(200, 200);
	Objs::InsertObj(Wall, OBJ_WALL, 6);
	//�E
	CObjWall2* Wall2 = new CObjWall2(200, 200);
	Objs::InsertObj(Wall2, OBJ_WALL, 6);
	//��
	CObjWall3* Wall3 = new CObjWall3(200, 200);
	Objs::InsertObj(Wall3, OBJ_WALL, 6);
	//��
	CObjWall4* Wall4 = new CObjWall4(200, 200);
	Objs::InsertObj(Wall4, OBJ_WALL, 6);

	//�t�H���g
	//�A�C�e���l���t�H���g�I�u�W�F�N�g�쐬
	CObjAitemFont* obj_af = new CObjAitemFont();
	Objs::InsertObj(obj_af, OBJ_AITEM_FONT, 20);

	//�X�e�[�W�㕔�w�i�I�u�W�F�N�g�쐬
	CObjTopback* objtb = new CObjTopback();
	Objs::InsertObj(objtb, OBJ_TOPBACK, 19);

	//�X�e�[�W�I�u�W�F�N�g�쐬
	CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 20);

	//�^�C���I�u�W�F�N�g�쐬
	CObjTime*objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 20);

	//�C�x���g�^�C���I�u�W�F�N�g�쐬
	CObjEvent*objev = new CObjEvent();
	Objs::InsertObj(objev, OBJ_EVENT, 20);

}

void CSceneStage::Scene()
{
	//���j���I�u�W�F�N�g�쐬����
	if (Input::GetVKey('E') == true)
	{
		//���j���[�I�u�W�F�N�g�쐬
		CObjMenu* obj_m = new CObjMenu();
		Objs::InsertObj(obj_m, OBJ_MENU, 21);
	}
}