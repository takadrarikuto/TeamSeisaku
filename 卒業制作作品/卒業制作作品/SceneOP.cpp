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
#include "ObjOP.h"
#include "SceneOP.h"

//�R���X�g���N�^
CSceneOP::CSceneOP()
{

}

//�f�X�g���N�^
CSceneOP::~CSceneOP()
{

}

//�Q�[�����C�����������\�b�h
void CSceneOP::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Draw::LoadImage(L"�^�C�g��.png", 3, TEX_SIZE_1024);

	//�I�u�W�F�N�g�쐬
	CObjOP* back = new CObjOP();
	Objs::InsertObj(back, OBJ_OP, 3);

	//���y�ǂݍ���
	//Audio::LoadAudio(0, L"���炷��BGM.wav", BACK_MUSIC);
	//�{�����[����1.0�ɖ߂�
	//float v = Audio::VolumeMaster(1.5);

	//���y�X�^�[�g
	//Audio::Start(0);

}

//�Q�[�����C�����s�����\�b�h
void CSceneOP::Scene()
{

}
