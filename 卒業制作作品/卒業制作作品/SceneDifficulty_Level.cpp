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
#include "ObjDifficulty_Level.h"

//�R���X�g���N�^
CSceneDifficulty_Level::CSceneDifficulty_Level()
{

}

//�f�X�g���N�^
CSceneDifficulty_Level::~CSceneDifficulty_Level()
{

}

//�Q�[�����C�����������\�b�h
void CSceneDifficulty_Level::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	Draw::LoadImage(L"��Փx�w�i.png", 3, TEX_SIZE_1024);

	//�^�C�g���I�u�W�F�N�g�쐬
	ObjDifficulty_Level* Level = new ObjDifficulty_Level();
	Objs::InsertObj(Level, OBJ_LEVEL, 3);

	//���y���̓ǂݍ���
	Audio::LoadAudio(0, L"�I����.wav", EFFECT);
	Audio::LoadAudio(1, L"���艹.wav", EFFECT);
	Audio::LoadAudio(2, L"�^�C�g��BGM.wav", BACK_MUSIC);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	Audio::Start(2);    //���y�X�^�[�g

}

//�Q�[�����C�����s�����\�b�h
void CSceneDifficulty_Level::Scene()
{

}