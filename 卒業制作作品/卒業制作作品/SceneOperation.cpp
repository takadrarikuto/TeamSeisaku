//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include"GameL\DrawTexture.h"
#include"GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "SceneStage.h"
#include "GameHead.h"
#include "SceneOperation.h"
#include "ObjOperation.h"

//�R���X�g���N�^
CSceneOperation::CSceneOperation()
{

}

//�f�X�g���N�^
CSceneOperation::~CSceneOperation()
{

}

//�Q�[�����C�����������\�b�h
void CSceneOperation::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	Draw::LoadImage(L"�������.png", 3, TEX_SIZE_1024);

	//�I�u�W�F�N�g�쐬
	CObjOperation* ope = new CObjOperation();
	Objs::InsertObj(ope, OBJ_OPERATION, 3);

	//���y���̓ǂݍ���
	//Audio::LoadAudio(0, L"���艹.wav", EFFECT);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	//float Volume = Audio::VolumeMaster(0.5);
}

//�Q�[�����C�����s�����\�b�h
void CSceneOperation::Scene()
{

}