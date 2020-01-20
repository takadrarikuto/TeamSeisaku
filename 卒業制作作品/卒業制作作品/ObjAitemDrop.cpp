//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include <time.h>

#include "GameHead.h"
#include "ObjAitemDrop.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjAitemDrop::Init()
{
//������
	//�A�C�e���h���b�v�t���O
	m_Aitem_Drop_flg = false; 
	//�A�C�e�������_���I��ϐ�
	m_Aitem_Rand_num = 0; 

//�ǂ̃G�l�~�[����h���b�v���邩�m�F����t���O
	m_Zombie_Drop_flg = false; //�]���r
	m_Fire_Lizard_Drop_flg = false; //�΃g�J�Q
	Bat_Drop_flg = false; //��
//�G�l�~�[�ʂō��W���L�^����
	Z_X= 0.0f; //�]���r
	Z_Y= 0.0f;
	FL_X= 0.0f; //�΃g�J�Q
	FL_Y= 0.0f;
	B_X= 0.0f; //��
	B_Y= 0.0f;

}

//�A�N�V����
void CObjAitemDrop::Action()
{
	//�G�ʒu�擾
	CObjZombieEnemy* Zombie = (CObjZombieEnemy*)Objs::GetObj(OBJ_ENEMY); //�]���r
	CObjFire_Lizard* Fire_Lizard = (CObjFire_Lizard*)Objs::GetObj(OBJ_FIRE_LIZARD); //�΃g�J�Q
	CObjBat_Enemy* Bat = (CObjBat_Enemy*)Objs::GetObj(OBJ_BAT_ENEMY); //��
	if (Zombie != nullptr)
	{
		Z_X = Zombie->GetX();
		Z_Y = Zombie->GetY();
	}
	if (Fire_Lizard != nullptr)
	{
		FL_X = Fire_Lizard->GetX();
		FL_Y = Fire_Lizard->GetY();
	}
	if (Bat != nullptr)
	{
		B_X = Bat->GetX();
		B_Y = Bat->GetY();
	}

	if (m_Aitem_Drop_flg == true)
	{
		m_Aitem_Rand_num = rand() % 100;
		if (m_Aitem_Rand_num < 80)
		{
			; //�h���b�v���Ȃ�
		}
		else if (m_Aitem_Rand_num >= 80 && m_Aitem_Rand_num < 85)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//��
				CObjHeal* Heal = new CObjHeal(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(Heal, OBJ_HEAL, 7);
				
				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//��
				CObjHeal* Heal = new CObjHeal(FL_X + 15, FL_Y + 20);
				Objs::InsertObj(Heal, OBJ_HEAL, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{
				//��
				CObjHeal* Heal = new CObjHeal(B_X + 15, B_Y + 20);
				Objs::InsertObj(Heal, OBJ_HEAL, 7);

				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		else if (m_Aitem_Rand_num >= 85 && m_Aitem_Rand_num < 90)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//�A�[�}�[
				CObjArmor* Armor = new CObjArmor(Z_X + 15, Z_Y + 10);
				Objs::InsertObj(Armor, OBJ_ARMOR, 7);				

				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//�A�[�}�[
				CObjArmor* Armor = new CObjArmor(FL_X + 15, FL_Y + 10);
				Objs::InsertObj(Armor, OBJ_ARMOR, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{
				//�A�[�}�[
				CObjArmor* Armor = new CObjArmor(B_X + 15, B_Y + 10);
				Objs::InsertObj(Armor, OBJ_ARMOR, 7);

				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		else if (m_Aitem_Rand_num >= 90 && m_Aitem_Rand_num < 95)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//�V���b�g�K���e��[
				CObjShotGunItem* SGi = new CObjShotGunItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);			

				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//�V���b�g�K���e��[
				CObjShotGunItem* SGi = new CObjShotGunItem(FL_X + 15, FL_Y + 20);
				Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{//�V���b�g�K���e��[
				CObjShotGunItem* SGi = new CObjShotGunItem(B_X + 15, B_Y + 20);
				Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);


				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		else if (m_Aitem_Rand_num >= 95 && m_Aitem_Rand_num < 98)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//�A�T���g���C�t���e��[
				CObjARItem* ARi = new CObjARItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);				

				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//�A�T���g���C�t���e��[
				CObjARItem* ARi = new CObjARItem(FL_X + 15, FL_Y + 20);
				Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{
				//�A�T���g���C�t���e��[
				CObjARItem* ARi = new CObjARItem(B_X + 15, B_Y + 20);
				Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);

				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		else if (m_Aitem_Rand_num >= 98 && m_Aitem_Rand_num < 100)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//�X�i�C�p�[���C�t���e��[
				CObjSniperRifleItem* SRi = new CObjSniperRifleItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);

				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//�X�i�C�p�[���C�t���e��[
				CObjSniperRifleItem* SRi = new CObjSniperRifleItem(FL_X + 15, FL_Y + 20);
				Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{
				//�X�i�C�p�[���C�t���e��[
				CObjSniperRifleItem* SRi = new CObjSniperRifleItem(B_X + 15, B_Y + 20);
				Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);

				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		m_Aitem_Drop_flg = false;
	}
	else if (m_Aitem_Drop_flg == false)
	{
		m_Aitem_Rand_num = 0;
	}
}

//�h���[
void CObjAitemDrop::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };


}