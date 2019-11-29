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
//#include "SceneMain.h"
#include "GameHead.h"
#include "SceneTitle.h"
#include "ObjTitle.h"

//�R���X�g���N�^
CSceneTitle::CSceneTitle()
{

}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//�Q�[�����C�����������\�b�h
void CSceneTitle::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	Draw::LoadImage(L"SCP354�^�C�g��.png", 3, TEX_SIZE_1024);
	Draw::LoadImage(L"�^�C�g��SCP���S.png", 4, TEX_SIZE_1024);

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjTitle* back = new CObjTitle();
	Objs::InsertObj(back, OBJ_TITLE, 3);
	
	//���y���̓ǂݍ���
	Audio::LoadAudio(0, L"�I����.wav", EFFECT);
	Audio::LoadAudio(1, L"���艹.wav", EFFECT);
	Audio::LoadAudio(2, L"�^�C�g��BGM.wav", BACK_MUSIC);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	//�{�����[����-0.3�ɂ���
	float v = Audio::VolumeMaster(-0.3);
	Audio::Start(2);    //���y�X�^�[�g
	
}

//�Q�[�����C�����s�����\�b�h
void CSceneTitle::Scene()
{

}