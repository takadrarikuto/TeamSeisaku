//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneClear.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneClear::CSceneClear()
{

}

//�f�X�g���N�^
CSceneClear::~CSceneClear()
{

}

//���������\�b�h
void CSceneClear::InitScene()
{

	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Draw::LoadImage(L"GAMECLEAR2.png", 4, TEX_SIZE_256);

	//�w�i�I�u�W�F�N�g�쐬
	CObjClear* nk = new CObjClear();
	Objs::InsertObj(nk, OBJ_CLEAR, 4);

	//���y�ǂݍ���
	//Audio::LoadAudio(0, L"�Q�[���N���ABGM.wav", BACK_MUSIC);
	//Audio::LoadAudio(1, L"���艹.wav", EFFECT);

	//�{�����[����1.0�ɖ߂�
	//float v = Audio::VolumeMaster(-0.1);

	//���y�X�^�[�g
	//Audio::Start(0);
}
//���s�����\�b�h
void CSceneClear::Scene()
{

}