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

//�g�p�w�b�_�[
#include "GameHead.h"
#include "SceneOver.h"

//���s�����\�b�h
void CSceneOver::Scene()
{

}

//�R���X�g���N�^
CSceneOver::CSceneOver()
{
}

//�f�X�g���N�^
CSceneOver::~CSceneOver()
{
}

//���������\�b�h
void CSceneOver::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	Draw::LoadImage(L"�Q�[���I�[�o�[.png", 3, TEX_SIZE_512);

	//�w�i�I�u�W�F�N�g�쐬
	CObjOver* go1 = new CObjOver();
	Objs::InsertObj(go1, OBJ_OVER, 4);
	
	//���y�ǂݍ���
	Audio::LoadAudio(0, L"�I����.wav", EFFECT);
	Audio::LoadAudio(1, L"���艹.wav", EFFECT);
	/*Audio::LoadAudio(2, L"�Q�[���I�[�o�[BGM.wav", BACK_MUSIC);
	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0.1);

	//���y�X�^�[�g
	Audio::Start(2);*/
}
