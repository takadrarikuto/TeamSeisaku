//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjGrenadeAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�R���X�g���N�^
CObjGrenadeAttack::CObjGrenadeAttack(float x, float y, float vx, float vy)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Grex = x;
	m_Grey = y;
	//�ړ��x�N�g��
	m_Grevx = vx;
	m_Grevy = vy;
}

//�C�j�V�����C�Y
void CObjGrenadeAttack::Init()
{
	//������
	//��~�ʒu
	Stop_max = 3; 

	//�_���[�W��
	((UserData*)Save::GetData())->GRE_Attack;

	//���j����
	EXP_time = 0;

	//�`��T�C�Y
	m_dst_size = 15.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 15;

	//�����E�����Ԃ��p�`��T�C�Y
	m_exp_blood_dst_size = 192.0f;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Grex, m_Grey, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 2);

}

//�A�N�V����
void CObjGrenadeAttack::Action()
{
	////SE����
	//if (Attack_flg == true)
	//{
	//	Audio::Start(1); //���y�X�^�[�g
	//	Attack_flg = false; //Attack�t���Ofalse
	//}	

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		//��l���ʒu�擾
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float hx = hero->GetX();
		float hy = hero->GetY();
		float hvx = hero->GetVX();
		float hvy = hero->GetVY();
		
		//���j����
		EXP_time++;
		//�ʒu�X�V
		//��l���̈ړ��ɍ��킹��
		m_Grex += (-hvx) + m_Grevx;
		m_Grey += (-hvy) + m_Grevy;


		//HitBox�̓��e���X�V 
		CHitBox* hit_gre = Hits::GetHitBox(this); //�����蔻����擾
		hit_gre->SetPos(m_Grex, m_Grey); //�����蔻��̈ʒu�X�V


		//��l�����痣���ƃI�u�W�F�N�g�ړ���~
		if (m_Grex < hx - 64 * Stop_max || m_Grex > hx + 32 + 64 * Stop_max
			|| m_Grey < hy - 64 * Stop_max || m_Grey > hy + 32 + 64 * Stop_max 
			|| hit_gre->CheckElementHit(ELEMENT_FIELD) == true)
		{
			//�ړ���~
			m_Grevx = 0.0f;
			m_Grevy = 0.0f;
		}

		if (EXP_time >= 180)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_Grex - 80, m_Grey - 90, m_exp_blood_dst_size, ((UserData*)Save::GetData())->GRE_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}

		//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
		if (hit_gre->CheckElementHit(ELEMENT_ENEMY) == true)
		{
			if (hit_gre->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_gre->CheckObjNameHit(OBJ_BOSS) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr)
			{
				; //�΂̒��A�~�[������(���{�X)�A�{�X�ɂ͓�����Ȃ�
			}
			else
			{
				//�����I�u�W�F�N�g�쐬
				CObjExplosion* obj_bs = new CObjExplosion(m_Grex - 80, m_Grey - 90, m_exp_blood_dst_size, ((UserData*)Save::GetData())->GRE_Attack);
				Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

				this->SetStatus(false); //�I�u�W�F�N�g�j��
				Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
			}
		}
	}
}

//�h���[
void CObjGrenadeAttack::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 320.0f;
	src.m_left = 15.0f;
	src.m_right = 30.0f;
	src.m_bottom = 330.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_Grey;
	dst.m_left = 0.0f + m_Grex;
	dst.m_right = m_dst_size + m_Grex;
	dst.m_bottom = m_dst_size + m_Grey;

	Draw::Draw(2, &src, &dst, c, 0.0f);

}