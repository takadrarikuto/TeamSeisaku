#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//�g�p����GameL�w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include <time.h>

#include "GameHead.h"
#include "SceneStage.h"

CSceneStage::CSceneStage()
{

}

CSceneStage::~CSceneStage()
{

}

void CSceneStage::InitScene()
{
	//�O���t�B�b�N�ǂݍ���
	//Draw::LoadImage(L"�F�����1.png", 0, TEX_SIZE_512);
	Draw::LoadImage(L"���m�E�R�l.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"�����Ԃ�.png", 10, TEX_SIZE_512);

	//���y���ǂݍ���
	//Audio::LoadAudio(0, L"�X�e�[�WBGM.wav", SOUND_TYPE::BACK_MUSIC);

	////�o�b�N�~���[�W�b�N�X�^�[�g
	////�{�����[����0.6�ɂ���
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster(0.6 - v);

	//Audio::Start(0); //���y�X�^�[�g


	//��l���@�I�u�W�F�N�g�쐬
	CObjHero* obj_h = new CObjHero(378.0f, 300.0f);
	Objs::InsertObj(obj_h, OBJ_HERO, 2);


	//�G�l�~�[�o���^�C��������
	e_time = 0;
	//�A�C�e���o���^�C��������
	i_time = 0;
	//�A�C�e���o��x�ʒu������
	i_x = 0.0f;

	//�V�[���؂�ւ��^�C��
	Scene_time = 0;
	//�Q�[���I�[�o�[�ړ�����
	GameOver_time = 0;


	/*
	//�G�@�I�u�W�F�N�g�쐬
	CObjEnemy* obj_e = new CObjEnemy();
	Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
	*/

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
	//if (Menu_flg == false)
	{
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