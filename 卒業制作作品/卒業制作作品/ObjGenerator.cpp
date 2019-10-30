//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjGenerator.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGenerator::CObjGenerator(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Genx = x;
	m_Geny = y;
	
}

//�C�j�V�����C�Y
void CObjGenerator::Init()
{
	//������
	m_Genvx = 0.0f; //�ʒu�X�V
	m_Genvy = 0.0f;

	m_Start_flg = false; //�v���J�n�t���O

	//�`��T�C�Y
	m_dst_size = 100.0f; 
	//�����蔻��T�C�Y
	Hitbox_size = 100; 

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Genx, m_Geny, Hitbox_size, 40, ELEMENT_FIELD, OBJ_APPARATUS, 6);
}

//�A�N�V����
void CObjGenerator::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();
	
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Genx, m_Geny); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && TStop_flg == true)
		{
			TStart_flg = true;
			time->SetTStart(TStart_flg);
		}
	}
	else
	{
		TStart_flg = false;
	}
	
	//��l���̈ړ��ɍ��킹��
	m_Genx -= hvx;
	m_Geny -= hvy;
}

//�h���[
void CObjGenerator::Draw()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();

	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Geny;
	dst.m_left = 0.0f + m_Genx;
	dst.m_right = m_dst_size + m_Genx;
	dst.m_bottom = m_dst_size + m_Geny;

	if (TStop_flg == true)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (TStop_flg == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}