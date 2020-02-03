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

//HP ONOFF�t���O
extern bool Hp_flg;

//�ϋv��ONOFF�t���O
extern bool En_flg;

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
	//��l���ʒu�擾�p
	hy = 0.0f;
	hx = 0.0f;
	//��l���x�N�g���擾�p
	hvx = 0.0f;
	hvy = 0.0f;

	//��~�ʒu
	Stop_max = 3; 

	//�_���[�W��
	//�ϋv�̓t���O���I���̎�
	if (En_flg == true)
	{
		m_EXPDameg_num = 50; //�����_���[�W
	}
	//�̗̓t���O���I���̎�
	if (Hp_flg == true)
	{
		m_EXPDameg_num = 100; //�����_���[�W
	}

	//���j����
	EXP_time = 0;

	//�`��T�C�Y
	m_dst_size = 15.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 15;

	//�����E�����Ԃ��p�`��T�C�Y
	m_exp_blood_dst_size = 192.0f;

	//HitBox�폜�t���O
	m_HitBox_Delete = false;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Grex, m_Grey, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 2);

}

//�A�N�V����
void CObjGrenadeAttack::Action()
{
	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();
	
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�`���[�g���A����l�����擾
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false)
	{
		//��l���A�`���[�g���A����l���̂ǂ��炩����������Ă��鎞
		//��l���p
		if (hero != nullptr)
		{
			hx = hero->GetX();
			hy = hero->GetY();
			hvx = hero->GetVX();
			hvy = hero->GetVY();	
		}
		//�`���[�g���A����l���p
		if (Tuhero != nullptr)
		{
			hx = Tuhero->GetX();
			hy = Tuhero->GetY();
			hvx = Tuhero->GetVX();
			hvy = Tuhero->GetVY();
		}
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
			|| hit_gre->CheckElementHit(ELEMENT_FIELD) == true || hit_gre->CheckElementHit(ELEMENT_FIELD2) == true
			|| hit_gre->CheckElementHit(ELEMENT_WALL) == true  || hit_gre->CheckElementHit(ELEMENT_WALL2) == true
			|| hit_gre->CheckElementHit(ELEMENT_NET_S) == true || hit_gre->CheckElementHit(ELEMENT_NET_V) == true
			|| hit_gre->CheckElementHit(ELEMENT_BARBED_V) == true)
		{
			//�t�B�[���h�G�������g�A�ǃG�������g�ƐڐG����ƍ폜
			if (hit_gre->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_gre->CheckObjNameHit(OBJ_ARMOR) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_gre->CheckObjNameHit(OBJ_HEAL) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_gre->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_gre->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_TOOLBOX) != nullptr || hit_gre->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
			{
				; //�A�C�e���n�@�������L�h�S���ɂ͓�����Ȃ�
			}
			else
			{
				//�ړ���~
				m_Grevx = 0.0f;
				m_Grevy = 0.0f;				
			}	
		}		
		if (EXP_time >= 180)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_Grex - 80, m_Grey - 90, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}

		//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
		if (hit_gre->CheckElementHit(ELEMENT_ENEMY) == true)
		{
			if (hit_gre->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_gre->CheckObjNameHit(OBJ_BOSS) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr 
				|| hit_gre->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
			{
				; //�΂̒��A�~�[������(���{�X)�A�{�X�A�������L�h�S���ɂ͓�����Ȃ�
			}
			else
			{
				//�����I�u�W�F�N�g�쐬
				CObjExplosion* obj_bs = new CObjExplosion(m_Grex - 80, m_Grey - 90, m_exp_blood_dst_size, m_EXPDameg_num);
				Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
				Audio::Start(9);

				m_HitBox_Delete = true;
			}
		}
	}

	//�폜����
	if (m_HitBox_Delete == true)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����

		m_HitBox_Delete = false; //������
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