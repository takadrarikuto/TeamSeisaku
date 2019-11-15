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
	//�{�����[����0.6�ɂ���
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.6 - v);

	Audio::Start(0); //���y�X�^�[�g
	*/

	//�G�l�~�[�o���^�C��������
	e_time = 0;
	//�A�C�e���o���^�C��������
	i_time = 0;
	//�A�C�e���o���ʒu������
	i_x = 0.0f;
	//�A�C�e���o���ʒu
	i_x = 0.0f;
	i_y = 0.0f;

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
	CObjBoss*obj_boss = new CObjBoss(832, 632);
	Objs::InsertObj(obj_boss, OBJ_BOSS, 2);

	//�΃g�J�Q�I�u�W�F�N�g�쐬 
	CObjFire_Lizard * obj_fl = new CObjFire_Lizard(100, 100);
	Objs::InsertObj(obj_fl, OBJ_FIRE_LIZARD, 4);

	//���d�@�I�u�W�F�N�g�쐬	
	CObjGenerator* Gen = new CObjGenerator(200, 200);
	Objs::InsertObj(Gen, OBJ_APPARATUS, 2);

	//�G���͉����u�I�u�W�F�N�g�쐬
	CObjEnemy_Neutralization_Device* END = new CObjEnemy_Neutralization_Device(400, 200);
	Objs::InsertObj(END, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 2);

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

	//�ǃI�u�W�F�N�g�쐬
	//��
	CObjWall* Wall = new CObjWall(200, 200);
	Objs::InsertObj(Wall, OBJ_WALL, 7);
	//�E
	CObjWall2* Wall2 = new CObjWall2(200, 200);
	Objs::InsertObj(Wall2, OBJ_WALL, 7);
	//��
	CObjWall3* Wall3 = new CObjWall3(200, 200);
	Objs::InsertObj(Wall3, OBJ_WALL, 7);
	//��
	CObjWall4* Wall4 = new CObjWall4(200, 200);
	Objs::InsertObj(Wall4, OBJ_WALL, 7);

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
	//�Q�[���I�[�o�[�V�[���ړ�����
	//if (GameOver_flg == true)
	//{
	//	GameOver_time++;
	//}
	//if (GameOver_time == 60)
	//{
	//	//�t���O�E�^�C��������
	//	GameOver_flg = false;
	//	GameOver_time = 0;
	//	//�Q�[���I�[�o�[��ʈړ�
	//	Scene::SetScene(new CSceneGameOver());
	//}

	//���j���[��ʉ{�����s����~����
	if (Menu_flg == false)
	{
		//�{�X��|�����班�����Ԃ��󂯂Ă���V�[���ړ�����
		/*if (boss_count == 1)
		{
			Scene_time++;
		}*/
		if (Scene_time == 60)
		{
			//�{�X�J�E���g�E�V�[���^�C��������
			//boss_count = 0;
			Scene_time = 0;
		}

		//e_time++;
		//if (e_time == 90)
		//{
		//	e_x = rand() % 736;
		//	e_y = rand() % 536;
		//	//�G�@�I�u�W�F�N�g�쐬
		//	CObjZombieEnemy* obj_ze = new CObjZombieEnemy(e_x, e_y);
		//	Objs::InsertObj(obj_ze, OBJ_ENEMY, 4);
		//}		

	//���j���[��ʉ{�����s����~����
	//if (Menu_flg == false)
	//{
		//�e�^�C������
		//e_time++;
		//i_time++;

		////�G�@�I�u�W�F�N�g�쐬
		//CObjEnemy* obj_e;
		////�A���G�@�I�u�W�F�N�g�쐬
		//CObjLinkingEnemy* obj_le;
		////�J�[�u�G�@�I�u�W�F�N�g����
		//CObjCurveEnemy* obj_ce;
		////�g�U�G�@�I�u�W�F�N�g����
		//CObjDiffusionEnemy* obj_de;
		////���e�I�u�W�F�N�g�쐬
		//CObjBomd* obj_b;

		//�G�o������
		//if (e_time == 90)
		//{
		//	//�G�@�I�u�W�F�N�g�쐬
		//	obj_e = new CObjEnemy(378.0f, -32.0f);
		//	Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//	if (Usually_flg == true)
		//	{
		//		//�G�@�I�u�W�F�N�g�쐬
		//		obj_e = new CObjEnemy(178.0f, -32.0f);
		//		Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//		obj_e = new CObjEnemy(578.0f, -32.0f);
		//		Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//	}
		//}

		//i_x = rand() % 770;

		//if (i_time == 600)
		//{
		//	//HP�񕜃A�C�e���I�u�W�F�N�g�쐬
		//	CObjHPupItem* obj_hi = new CObjHPupItem(i_x, -30.0f);
		//	Objs::InsertObj(obj_hi, OBJ_ITEM, 2);

		//	srand(time(NULL)); // �����_������������
		//	i_time = 0;
		//}
	}
}