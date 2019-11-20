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
	OBJ_GUNATTACK,
	OBJ_SHOTGUNATTACK,
	OBJ_ARATTACK,
	OBJ_SNIPERRIFLEATTACK,
	OBJ_ROCKETLAUNCHERATTACK,
	OBJ_RAILGUNATTACK,
	OBJ_GRENADEATTACK,
	OBJ_ENEMY,
	OBJ_FIRE_BIRD,
	OBJ_FIRE_LIZARD,
	OBJ_BAT_ENEMY,
	OBJ_SPHERE_TYPE_ENEMY,
	OBJ_MEME_MEDIUM_BOSS,
	OBJ_BOSS,
	OBJ_APPARATUS,
	OBJ_ENEMY_NEUTRALIZATION_DEVICE,
	OBJ_BLOOD_SPLASH,
	OBJ_EXPLOSION,
	OBJ_OBJECT,
	OBJ_TUTORIAL,
	OBJ_STAGE,
	OBJ_TITLE,
	OBJ_OP,
	OBJ_OPERATION,
	OBJ_CLEAR,
	OBJ_OVER,
	OBJ_ED,
	OBJ_MENU,
	OBJ_TOPBACK,
	OBJ_BACKGROUND,
	OBJ_AIMING,
	OBJ_HEAL,
	OBJ_EVENT,
	OBJ_SHOTGUN_ITEM,
	OBJ_AR_ITEM,
	OBJ_SNIPERRIFLE_ITEM,
	OBJ_ROCKETLAUNCHER_ITEM,
	OBJ_RAILGUN_ITEM,
	OBJ_GRENADE_ITEM,
	OBJ_WALL,
	OBJ_TUTO_HERO,
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
	ELEMENT_WALL,
	ELEMENT_WALL2,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	//����ʃ_���[�W
	int Gun_Attack = 10;  //�n���h�K��
	int SHG_Attack = 30;	//�V���b�g�K��
	int AR_Attack = 20; //�A�T���g���C�t��
	int SR_Attack = 50; //�X�i�C�p�[���C�t��
	int RL_Attack = 150; //���P�b�g�����`���[
	int RG_Attack = 200; //���[���K��
	int GRE_Attack = 100;	//�O���l�[�h
	int EXP_Attack = 50; //����

};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--

extern int g_zombie_count_tu;//�`���[�g���A���G���j���p

//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------
//�x�[�X�f�[�^
#include "BaseStatus.h"

//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
//��l��
#include "ObjHero.h"

//��l���p�U��
#include "ObjGunAttack.h"
#include "ObjShotGunAttack.h"
#include "ObjARAttack.h"
#include "ObjSniperRifleAttack.h"
#include "ObjRocketLauncherAttack.h"
#include "ObjRailGunAttack.h"
#include "ObjGrenadeAttack.h"

//�W��
#include "ObjAiming.h"

//�G�l�~�[
#include "ObjZombieEnemy.h"
#include "ObjFire_Bird.h"
#include "ObjFire_Lizard.h"
#include "ObjBat_Enemy.h"
#include "ObjSphere_Type_Enemy.h"

//���{�X
#include "ObjMeme_Medium_Boss.h"

//�{�X
#include "ObjBoss.h"

//�G�l�~�[�E���{�X�E�{�X�p�U��
//���S�G�t�F�N�g
#include "ObjBlood_splash.h"

//����
#include "ObjExplosion.h"

//�X�e�[�W
#include "ObjStage.h"

//�ݒu��
#include "ObjGenerator.h"
#include "ObjGenerator2.h"
#include "ObjEnemy_Neutralization_Device.h"
#include "ObjEnemy_Neutralization_Device2.h"

//�A�C�e��
#include "ObjHeal.h"//��
#include "ObjShotGunItem.h"//�V���b�g�K����[�p
#include "ObjARItem.h"//�A�T���g���C�t����[�p
#include "ObjSniperRifleItem.h"//�X�i�C�p�[���C�t����[�p
#include "ObjRocketLauncherItem.h"//���P�b�g�����`���[��[�p
#include "ObjRailGunItem.h"//���[���K����[�p
#include "ObjGrenadeItem.h"//�O���l�[�h��[�p

//�C�x���g
#include "ObjEvent.h"

//�^�C�g��
#include "ObjTitle.h"

//���炷��
#include "ObjOP.h"

//�������
#include "ObjOperation.h"

//�`���[�g���A��
#include "ObjTutorial.h"
//�`���[�g���A���p
#include "ObjTutoHero.h"
#include "ObjTutoBg.h"
#include "ObjTutoTopback.h"
#include "ObjTutoZombieEnemy.h"
#include "ObjTutoWall.h"
#include "ObjTutoWall2.h"
#include "ObjTutoWall3.h"
#include "ObjTutoWall4.h"

//�Q�[���I�[�o�[
#include "ObjOver.h"

//�N���A
#include "ObjClear.h"

//�G���f�B���O
#include "ObjED.h"

//���j���[
#include "ObjMenu.h"

//�^�C��
#include "ObjTime.h"

//�X�e�[�W�㕔UI�w�i
#include "ObjTopback.h"

//�w�i
#include "ObjBackground.h"

//��
#include "ObjWall.h"//��
#include "ObjWall2.h"//�E
#include "ObjWall3.h"//��
#include "ObjWall4.h"//��

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

//�`���[�g���A��
#include "SceneTutorial.h"

//�Q�[���I�[�o�[
#include "SceneOver.h"

//�N���A
#include "SceneClear.h"

//�G���f�B���O
#include "SceneED.h"

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START  CSceneStage