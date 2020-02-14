#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjAitemDrop :public CObj, public CBaseStatus
{
public:
	CObjAitemDrop() {};
	~CObjAitemDrop() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	void SetAitemDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //�A�C�e���h���b�v�t���O�ݒ�p
//�ǂ̃G�l�~�[����h���b�v���邩�m�F����t���O�ݒ�p
	void SetZombieDrop(bool zombie_drop) { m_Zombie_Drop_flg = zombie_drop; } //�]���r
	void SetFire_LizardDrop(bool fire_lizard_drop) { m_Fire_Lizard_Drop_flg = fire_lizard_drop; } //�΃g�J�Q
	void SetBatDrop(bool bat_drop) { Bat_Drop_flg = bat_drop; } //��
//�G�l�~�[���W�擾�ݒ�p
	void SetZombie_X(float z_x) { Z_X = z_x; } //�]���r
	void SetZombie_Y(float z_y) { Z_Y = z_y; }
	void SetFire_Lizard_X(float fl_x) { FL_X = fl_x; } //�΃g�J�Q
	void SetFire_Lizard_Y(float fl_y) { FL_Y = fl_y; }
	void SetBat_X(float b_x) { B_X = b_x; } //��
	void SetBat_Y(float b_y) { B_Y = b_y; }
private:
	bool m_Aitem_Drop_flg; //�A�C�e���h���b�v�t���O
	int m_Aitem_Rand_num; //�A�C�e�������_���I��ϐ�

//�ǂ̃G�l�~�[����h���b�v���邩�m�F����t���O
	bool m_Zombie_Drop_flg; //�]���r
	bool m_Fire_Lizard_Drop_flg; //�΃g�J�Q
	bool Bat_Drop_flg; //��
//�G�l�~�[�ʂō��W���L�^����
	float Z_X; //�]���r
	float Z_Y;
	float FL_X; //�΃g�J�Q
	float FL_Y;
	float B_X; //��
	float B_Y;

};