#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//�g�p����GameL�w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"
#include"GameL\DrawFont.h"
#include "GameL\Audio.h"

#include <time.h>

#include "GameHead.h"
#include "SceneStage.h"

//���j���[ONOFF�t���O
extern bool Menu_flg;

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
	//���{�X�p��5�͋󂯂�
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

	//�o�b�N�~���[�W�b�N�X�^�[�g
	float Volume = Audio::VolumeMaster(-0.3);

	Audio::Start(0); //���y�X�^�[�g
	

	//�G�l�~�[�o���^�C��������
	e_time = 0;
	//�A�C�e���o���^�C��������
	i_time = 0;
	//�A�C�e���o���ʒu
	i_x1 = -602.0f; //����
	i_y1 = -100.0f;

	//�V�[���؂�ւ��^�C��
	Scene_time = 0;
	//�Q�[���I�[�o�[�ړ�����
	GameOver_time = 0;

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
	CObjBoss*obj_boss = new CObjBoss(300, 400);
	Objs::InsertObj(obj_boss, OBJ_BOSS, 2);	

	//���d�@�I�u�W�F�N�g�쐬	
	CObjGenerator* Gen = new CObjGenerator(-300, -300);//(200,200)
	Objs::InsertObj(Gen, OBJ_GENERATOR, 2);

	CObjGenerator2* Gen2 = new CObjGenerator2(1200, 900);//(500,200)
	Objs::InsertObj(Gen2, OBJ_GENERATOR, 2);

	//�G���͉����u�I�u�W�F�N�g�쐬
	CObjEnemy_Neutralization_Device* END = new CObjEnemy_Neutralization_Device(1200, -300);//(400,200)
	Objs::InsertObj(END, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 2);

	CObjEnemy_Neutralization_Device2* END2 = new CObjEnemy_Neutralization_Device2(-300, 900);//(700,200)
	Objs::InsertObj(END2, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 2);

	//�~�[�����Ԗ��͉����u�I�u�W�F�N�g�쐬
	CObjMeme_Neutralization_Device* MND = new CObjMeme_Neutralization_Device(375, -400);
	Objs::InsertObj(MND, OBJ_MEME_NEUTRALIZATION_DEVICE, 2);

	//�L�h�S���I�u�W�F�N�g�쐬
	CObjBarbedWire* Barbed = new CObjBarbedWire(200, 200);
	Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 7);
	CObjBarbedWireSmall* BarbedS = new CObjBarbedWireSmall(200, 200);
	Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 7);
	
	//�ԃI�u�W�F�N�g�쐬 x=202 y=72
	CObjNet* Net = new CObjNet(800, 200);
	Objs::InsertObj(Net, OBJ_NET, 7);
	//�ԃI�u�W�F�N�g�쐬
	//����
	for (int x = -602; x < 206; x += 202)
	{
		Net = new CObjNet(x, -100);
		Objs::InsertObj(Net, OBJ_NET, 7);
	}
	/*CObjNet* Net2 = new CObjNet(-400, -100);
	Objs::InsertObj(Net2, OBJ_NET, 7);
	Net = new CObjNet(-602, -100);
	Objs::InsertObj(Net, OBJ_NET, 7);*/
	
	//�A�C�e���I�u�W�F�N�g�쐬	
	//��
	CObjHeal* Heal = new CObjHeal(200, 200);
	Objs::InsertObj(Heal, OBJ_HEAL, 7);
	//�V���b�g�K���e��[
	CObjShotGunItem* SGi = new CObjShotGunItem(200, 200);
	Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);
	//�A�T���g���C�t���e��[
	CObjARItem* ARi = new CObjARItem(200, 200);
	Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);
	//�X�i�C�p�[���C�t���e��[
	CObjSniperRifleItem* SRi = new CObjSniperRifleItem(200, 200);
	Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);
	//���P�b�g�����`���[�e��[
	CObjRocketLauncherItem* RLi = new CObjRocketLauncherItem(200, 200);
	Objs::InsertObj(RLi, OBJ_ROCKETLAUNCHER_ITEM, 7);
	//���[���K���e��[
	CObjRailGunItem* RGi = new CObjRailGunItem(200, 200);
	Objs::InsertObj(RGi, OBJ_RAILGUN_ITEM, 7);
	//�O���l�[�h��[
	CObjGrenadeItem* GREi = new CObjGrenadeItem(200, 200);
	Objs::InsertObj(GREi, OBJ_GRENADE_ITEM, 7);
	//�A�[�}�[
	CObjArmor* Armor = new CObjArmor(200, 200);
	Objs::InsertObj(Armor, OBJ_ARMOR, 7);
	//�H�
	CObjToolBox* Toolbox = new CObjToolBox(200, 200);
	Objs::InsertObj(Toolbox, OBJ_TOOLBOX, 7);
	//�ݒu�^�V���b�g�K���e��[
	CObjInstallation_Type_ShotGun* obj_it_shg = new CObjInstallation_Type_ShotGun(-300, -640);
	Objs::InsertObj(obj_it_shg, OBJ_INSTALL_TYPE_SHG, 6);
	//�ݒu�^�A�T���g���C�t���e��[
	CObjInstallation_Type_AR* obj_it_ar = new CObjInstallation_Type_AR(1180, -640);
	Objs::InsertObj(obj_it_ar, OBJ_INSTALL_TYPE_AR, 6);

	//�ǃI�u�W�F�N�g�쐬
	//��
	CObjWall* Wall = new CObjWall(200, 200);
	Objs::InsertObj(Wall, OBJ_WALL, 5);
	//�E
	CObjWall2* Wall2 = new CObjWall2(200, 200);
	Objs::InsertObj(Wall2, OBJ_WALL, 5);
	//��
	CObjWall3* Wall3 = new CObjWall3(200, 200);
	Objs::InsertObj(Wall3, OBJ_WALL, 5);
	//��
	CObjWall4* Wall4 = new CObjWall4(200, 200);
	Objs::InsertObj(Wall4, OBJ_WALL, 5);

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

	//���y���ǂݍ��� 
	//Audio::LoadAudio(0, L"�X�e�[�WBGM.wav",BACK_MUSIC);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	//�{�����[����0.6�ɂ���
	//float v = Audio::VolumeMaster(0.6);

	//Audio::Start(0); //���y�X�^�[�g
	
}

void CSceneStage::Scene()
{
	//���j���[��ʉ{�����s����~����
	if (Menu_flg == false)
	{		

	}

}