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

//���j���[ONOFF�t���O
extern bool Menu_flg;

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
	//�G�l�~�[�o���^�C��������
	e_time = 0;
	//�A�C�e���o���^�C��������
	i_time = 0;
	//�A�C�e���o���ʒu������
	i_x = 0.0f;
	//�A�C�e���o���ʒu
	i_x = 0.0f;
	i_y = 0.0f;

	//�w�i�I�u�W�F�N�g�쐬
	C0bjBackground * back = new C0bjBackground();
	Objs::InsertObj(back, OBJ_BACKGROUND, 1);

	//�`���[�g���A���I�u�W�F�N�g�쐬
	CObjTutorial* tuto = new CObjTutorial();
	Objs::InsertObj(tuto, OBJ_TUTORIAL, 3);

	//��l���@�I�u�W�F�N�g�쐬
	CObjHero* obj_h = new CObjHero(350.0f, 280.0f);
	Objs::InsertObj(obj_h, OBJ_HERO, 8);

	//�X�e�[�W�㕔�w�i�I�u�W�F�N�g�쐬
	CObjTopback* objtb = new CObjTopback();
	Objs::InsertObj(objtb, OBJ_TOPBACK, 19);

	//�X�e�[�W�I�u�W�F�N�g�쐬
	CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 20);

	//���y���̓ǂݍ���
	Audio::LoadAudio(0, L"�I����.wav", EFFECT);
	Audio::LoadAudio(1, L"���艹.wav", EFFECT);
	Audio::LoadAudio(2, L"�^�C�g��BGM.wav", SOUND_TYPE::BACK_MUSIC);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	float Volume = Audio::VolumeMaster(0.5);
	Audio::Start(2);    //���y�X�^�[�g
}

//�Q�[�����C�����s�����\�b�h
void CSceneTutorial::Scene()
{

}