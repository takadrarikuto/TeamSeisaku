#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�w�i
class CObjTutoTopback : public CObj
{
public:
	CObjTutoTopback() {};
	~CObjTutoTopback() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	//int GetZoCoTu() { return g_zombie_count_tu; } //�`���[�g���A���G���j�������擾�p

	void SetZoCoTu(int Zo_Co_Tu) { g_zombie_count_tu_increase = Zo_Co_Tu; } //�`���[�g���A���G���j�������ݒ�p

private:
	//�e�c��e�����擾�p�ϐ�(������)
	int hg_pb_e;
	int sg_pb_e;
	int ar_pb_e;
	int sr_pb_e;
	int rl_pb_e;
	int rg_pb_e;

	int ws_num;

	int tuto_se_time;

	int g_zombie_count_tu; //�`���[�g���A���G���j���p
	int g_zombie_count_tu_increase;  //�`���[�g���A���G���j�������p
};
