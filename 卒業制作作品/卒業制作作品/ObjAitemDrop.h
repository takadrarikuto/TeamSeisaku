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
	void SetZombieDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //�]���r
	void SetFire_BirdDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //�΂̒�
	void SetFire_LizardDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //�΃g�J�Q
	void SetBatDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //��

private:
	bool m_Aitem_Drop_flg; //�A�C�e���h���b�v�t���O
	int m_Aitem_Rand_num; //�A�C�e�������_���I��ϐ�

//�ǂ̃G�l�~�[����h���b�v���邩�m�F����t���O
	bool m_Zombie_Drop_flg; //�]���r
	bool m_Fire_Bird_Drop_flg; //�΂̒�
	bool m_Fire_Lizard_Drop_flg; //�΃g�J�Q
	bool Bat_Drop_flg; //��

};