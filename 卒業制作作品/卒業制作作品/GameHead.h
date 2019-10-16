#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_HERO,
	OBJ_PER_DECISION,
	OBJ_TIME,
	OBJ_ENEMY,
	OBJ_BLOOD_SPLASH,
	OBJ_OBJECT,
	OBJ_TITLE,
	OBJ_OP,
	OBJ_OPERATION,
	OBJ_CLEAR,
	OBJ_OVER,
	OBJ_ED,
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--



//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------
//�x�[�X�f�[�^
#include "BaseStatus.h"

//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
//��l��
#include "ObjHero.h"

//��l���p�U��
//�G�l�~�[
//���{�X
//�{�X
//�G�l�~�[�E���{�X�E�{�X�p�U��
//���S�G�t�F�N�g
#include "ObjBlood_splash.h"

//�X�e�[�W

//�^�C�g��
#include "ObjTitle.h"

//���炷��
#include "ObjOP.h"

//�������
#include "ObjOperation.h"

//�Q�[���I�[�o�[
#include "ObjOver.h"

//�N���A
#include "ObjClear.h"

//�G���f�B���O
#include "ObjED.h"

//���j���[
#include "ObjMenu.h"

//�x�[�X�ݒ�
#include "GameHead.h"

//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
//�X�e�[�W
#include "SceneStage.h"

//�^�C�g��
#include "SceneTitle.h"

//���炷��
#include "SceneOP.h"

//�������
#include "SceneOperation.h"

//�Q�[���I�[�o�[
#include "SceneOver.h"

//�N���A
#include "SceneClear.h"

//�G���f�B���O
#include "SceneED.h"

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
//#define SET_GAME_START  CSceneStage

//�f�o�b�O�p
#define SET_GAME_START  CSceneOver
//-----------------------------------------------