//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h""
#include"GameL\DrawTexture.h"
#include"GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "GameHead.h"
#include "SceneTutorial.h"
#include "ObjTutorial.h"

//�R���X�g���N�^
CSceneTutorial::CSceneTutorial()
{

}

//�f�X�g���N�^
CSceneTutorial::~CSceneTutorial()
{

}

//�Q�[�����C�����������\�b�h
void CSceneTutorial::InitScene()
{
	m_tuto_time = 0;

	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"�X�e�[�W.png", 0, TEX_SIZE_512);
	Draw::LoadImage(L"�e�e�܂Ƃ�.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"���̒r.png", 3, TEX_SIZE_512);
	Draw::LoadImage(L"�G�l�~�[�܂Ƃ�.png", 4, TEX_SIZE_512);
	
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

	

	//�w�i�I�u�W�F�N�g�쐬(�`���[�g���A���p)
	CObjTutoBg * back_tu = new CObjTutoBg();
	Objs::InsertObj(back_tu, OBJ_BACKGROUND, 1);

	//�`���[�g���A���I�u�W�F�N�g�쐬
	CObjTutorial* tuto = new CObjTutorial();
	Objs::InsertObj(tuto, OBJ_TUTORIAL, 20);

	//��l���@�I�u�W�F�N�g�쐬(�`���[�g���A���p)
	CObjTutoHero* obj_h_tu = new CObjTutoHero(350.0f, 280.0f);
	Objs::InsertObj(obj_h_tu, OBJ_TUTO_HERO, 8);

	//�Ə��I�u�W�F�N�g�쐬
	CObjAiming* obj_ai = new CObjAiming();
	Objs::InsertObj(obj_ai, OBJ_AIMING, 12);

	//�X�e�[�W�㕔�w�i�I�u�W�F�N�g�쐬(�`���[�g���A���p)
	CObjTutoTopback* objtutb = new CObjTutoTopback();
	Objs::InsertObj(objtutb, OBJ_TOPBACK, 19);

	//�X�e�[�W�I�u�W�F�N�g�쐬(�`���[�g���A���p)
	CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 20);

	//�ǃI�u�W�F�N�g�쐬(�`���[�g���A���p)
	//��
	CObjTutoWall* tu_Wall = new CObjTutoWall(200, 200);
	Objs::InsertObj(tu_Wall, OBJ_WALL, 4);
	//�E
	CObjTutoWall2* tu_Wall2 = new CObjTutoWall2(200, 200);
	Objs::InsertObj(tu_Wall2, OBJ_WALL, 4);
	//��
	CObjTutoWall3* tu_Wall3 = new CObjTutoWall3(200, 200);
	Objs::InsertObj(tu_Wall3, OBJ_WALL, 4);
	//��
	CObjTutoWall4* tu_Wall4 = new CObjTutoWall4(200, 200);
	Objs::InsertObj(tu_Wall4, OBJ_WALL, 4);
	
	//���y���̓ǂݍ���
	Audio::LoadAudio(0, L"�`���[�g���A��BGM.wav", SOUND_TYPE::BACK_MUSIC);
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
	Audio::LoadAudio(18, L"������.wav", EFFECT);//�`���[�g���A���p

	//�o�b�N�~���[�W�b�N�X�^�[�g
	float Volume = Audio::VolumeMaster(-0.1);
	Audio::Start(0);    //���y�X�^�[�g
	
}

//�Q�[�����C�����s�����\�b�h
void CSceneTutorial::Scene()
{
	m_tuto_time++;

	//�G�@�I�u�W�F�N�g�쐬(�`���[�g���A���p)
	if (m_tuto_time == 1250)
	{
		CObjTutoZombieEnemy* obj_ze_tu;
		obj_ze_tu = new CObjTutoZombieEnemy(550.0f, 400.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(150.0f, 400.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(550.0f, 200.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(150.0f, 200.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(360.0f, 500.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(360.0f, 100.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		Audio::Start(11);
	}
}