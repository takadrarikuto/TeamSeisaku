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

	m_Starp_flg = false; //�v���J�n�t���O

	//�㉺���E�ʓ����蔻��m�F�t���O
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_LightHit_flg = false; //�E

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
	bool ST_flg = time->GetTS();

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Genx, m_Geny); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && ST_flg == true)
		{
			m_Starp_flg = true;
		}
	}
	else
	{
		m_Starp_flg = false;
	}
	
	//��l���̈ړ��ɍ��킹��
	m_Genx -= hvx;
	m_Geny -= hvy;

}

//�h���[
void CObjGenerator::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

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
	Draw::Draw(6, &src, &dst, c, 0.0f);



}