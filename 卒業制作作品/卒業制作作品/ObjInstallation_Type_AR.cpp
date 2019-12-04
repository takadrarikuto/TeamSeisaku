//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjInstallation_Type_AR.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjInstallation_Type_AR::CObjInstallation_Type_AR(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_IT_ARx = x;
	m_IT_ARy = y;

}

//�C�j�V�����C�Y
void CObjInstallation_Type_AR::Init()
{
	//������
	m_IT_ARvx = 0.0f; //�ʒu�X�V
	m_IT_ARvy = 0.0f;

	//�`��T�C�Y
	m_dst_size = 50.0f;

	//HitBox�T�C�Y
	m_HitSize_x = 100;
	m_HitSize_y = 60;

	//��[�t���O
	m_Replenishment_flg = false;
	//�ĕ�[�^�C��
	m_Replenishment_time = 0;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_IT_ARx, m_IT_ARy, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_AR, 6);

}

//�A�N�V����
void CObjInstallation_Type_AR::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBox�̓��e���X�V 
	CHitBox* hit_gen = Hits::GetHitBox(this); //�����蔻����擾 
	hit_gen->SetPos(m_IT_ARx, m_IT_ARy); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			hero->SetAR(90);
			aitemfont->SetAitemNum(90);
			aitemfont->SetAGF(2);
			Audio::Start(12); //���ʉ��Đ�
			//��[�t���O
			m_Replenishment_flg = true;
			//�ĕ�[�^�C��
			m_Replenishment_time = 600;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	//��l���̈ړ��ɍ��킹��
	m_IT_ARx -= hvx;
	m_IT_ARy -= hvy;

	//�ĕ�[�^�C��
	if (m_Replenishment_time > 0)
	{
		m_Replenishment_time--;
	}
}

//�h���[
void CObjInstallation_Type_AR::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 205.0f;
	src.m_left = 594.0f;
	src.m_right = 660.0f;
	src.m_bottom = 250.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_IT_ARy;
	dst.m_left = 0.0f + m_IT_ARx;
	dst.m_right = m_dst_size * 2 + m_IT_ARx;
	dst.m_bottom = m_dst_size + m_IT_ARy;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}