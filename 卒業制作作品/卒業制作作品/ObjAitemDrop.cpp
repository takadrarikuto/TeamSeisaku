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

}

//�A�N�V����
void CObjAitemDrop::Action()
{
	//�G�ʒu�擾
	//CObjZombieEnemy* Zombie = (CObjZombieEnemy*)Objs::GetObj(OBJ_ENEMY); //�]���r
	//CObjFire_Bird* Fire_Bird = (CObjFire_Bird*)Objs::GetObj(OBJ_FIRE_BIRD); //�΂̒�
	//CObjFire_Lizard* Fire_Lizard = (CObjFire_Lizard*)Objs::GetObj(OBJ_FIRE_LIZARD); //�΃g�J�Q
	//CObjBat_Enemy* Bat = (CObjBat_Enemy*)Objs::GetObj(OBJ_BAT_ENEMY); //��

	if (m_Aitem_Drop_flg == true)
	{
		/*m_Aitem_Rand_num = rand() % 100;*/
		m_Aitem_Rand_num = 1;
		if (m_Aitem_Rand_num == 0)
		{
			;
		}
		else if (m_Aitem_Rand_num == 1)
		{

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