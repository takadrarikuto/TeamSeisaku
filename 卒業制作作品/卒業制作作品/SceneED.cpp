//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "SceneStage.h"
#include "GameHead.h"
#include "ObjED.h"
#include "SceneED.h"

//�R���X�g���N�^
CSceneED::CSceneED()
{

}

//�f�X�g���N�^
CSceneED::~CSceneED()
{

}

//�Q�[�����C�����������\�b�h
void CSceneED::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	Draw::LoadImage(L"SCP354�^�C�g��.png", 3, TEX_SIZE_1024);

	//�I�u�W�F�N�g�쐬
	CObjED* back = new CObjED();
	Objs::InsertObj(back, OBJ_ED, 3);

	//���y�ǂݍ���
	Audio::LoadAudio(0, L"�G���f�B���O.wav", BACK_MUSIC);
	//�{�����[����1.0�ɖ߂�
	//float v = Audio::VolumeMaster(1.5);

	//���y�X�^�[�g
	Audio::Start(0);
}

//�Q�[�����C�����s�����\�b�h
void CSceneED::Scene()
{

}
