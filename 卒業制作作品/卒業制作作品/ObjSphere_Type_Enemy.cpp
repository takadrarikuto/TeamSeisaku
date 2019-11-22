//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjSphere_Type_Enemy.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//メニューキー制御用フラグ
extern bool m_key_flag_menu;

//HP ONOFFフラグ
extern bool Hp_flg;

//耐久力ONOFFフラグ
extern bool En_flg;

//コンストラクタ
CObjSphere_Type_Enemy::CObjSphere_Type_Enemy(float st_ex, float st_ey)
{
	//位置情報登録(数値=位置調整)
	m_st_ex = st_ex;
	m_st_ey = st_ey;
}

//イニシャライズ
void CObjSphere_Type_Enemy::Init()
{
	//初期化
	//移動ベクトル
	m_st_evx = 0.0f;
	m_st_evy = 0.0f;

	//体力
	m_hero_hp = 1;

	//移動ベクトル最大値
	m_st_ev_max = 2.0f;

	//移動フラグ
	m_st_e_x_flg = false;
	m_st_e_y_flg = false;

	//上下左右別当たり判定確認フラグ
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_RightHit_flg = false; //右

	//攻撃頻度
	m_at = 0;
	//攻撃頻度最大値
	m_at_max = 5;

	//死亡処理
	m_st_e_death_flg = false; //死亡フラグ

	//ダメージ
	//耐久力フラグがオンの時
	if (En_flg == true)
	{
		((UserData*)Save::GetData())->EXP_Attack = 25; //爆発
	}
	//体力フラグがオンの時
	if (Hp_flg == true)
	{
		((UserData*)Save::GetData())->EXP_Attack = 50; //爆発
	}

	//描画サイズ
	m_dst_size = 32.0f;
	//当たり判定サイズ
	Hitbox_size = 32;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 192;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_st_ex, m_st_ey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_SPHERE_TYPE_ENEMY, 4);
}

//アクション
void CObjSphere_Type_Enemy::Action()
{
	//上下左右別当たり判定確認フラグ初期化
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_RightHit_flg = false; //右

	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX() + 16; //位置
	float hy = hero->GetY() + 16;
	float hvx = hero->GetVX(); //移動ベクトル
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_st_ex; //位置更新
	float hpy = hero->GetPY() - m_st_ey;
	float h_HitBox = hero->GetHitBox(); //当たり判定
	bool h_gel = hero->GetDel(); //削除チェック

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//移動処理
		//主人公が上に居ると上に移動
		if (hy < m_st_ey)
		{
			m_st_evy = -m_st_ev_max;
		}
		//主人公が下に居ると下移動
		else if (hy > m_st_ey)
		{
			m_st_evy = m_st_ev_max;
		}
		//主人公が左に居ると左に移動
		if (hx < m_st_ex)
		{
			m_st_evx = -m_st_ev_max;
		}
		//主人公が右に居ると右に移動
		else if (hx > m_st_ex)
		{
			m_st_evx = m_st_ev_max;
		}
		if (hx == m_st_ex)
		{
			m_st_evx = 0.0f;
			//主人公が上に居ると上に移動
			if (hy < m_st_ey)
			{
				m_st_evy = -m_st_ev_max;
			}
			//主人公が下に居ると下移動
			else if (hy > m_st_ey)
			{
				m_st_evy = m_st_ev_max;
			}
		}
		else if (hy == m_st_ey)
		{
			m_st_evy = 0.0f;
			//主人公が左に居ると左に移動
			if (hx < m_st_ex)
			{
				m_st_evx = -m_st_ev_max;
			}
			//主人公が右に居ると右に移動
			else if (hx > m_st_ex)
			{
				m_st_evx = m_st_ev_max;
			}
		}

		//斜め移動修正処理
		float r = 0.0f;
		r = m_st_evx * m_st_evx + m_st_evy * m_st_evy;
		r = sqrt(r); //ルートを求める

		//斜めベクトルを求める
		if (r == 0.0f)
		{
			; //0なら何もしない
		}
		else
		{
			m_st_evx = m_st_ev_max / r * m_st_evx;
			m_st_evy = m_st_ev_max / r * m_st_evy;
		}

		//位置更新
		//主人公の移動を適応する
		m_st_ex += (-hvx) + m_st_evx;
		m_st_ey += (-hvy) + m_st_evy;
	}

	//HitBoxの内容を更新
	CHitBox* hit_st_e = Hits::GetHitBox(this); //当たり判定情報取得
	hit_st_e->SetPos(m_st_ex, m_st_ey); //当たり判定の位置更新

	//当たり判定処理
	if (hit_st_e->CheckElementHit(ELEMENT_WALL) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_st_e->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_st_e->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			//角度で上下左右を判定
			if ((r < 88 && r >= 0) || r > 292)
			{
				m_st_evx = -0.15f; //右
			}
			if (r > 88 && r < 92)
			{
				m_st_evy = 0.15f;//上
			}
			if (r > 92 && r < 268)
			{
				m_st_evx = 0.15f;//左
			}
			if (r > 268 && r < 292)
			{
				m_st_evy = -0.15f; //下
			}
		}
	}

	//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
	if (hit_st_e->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_st_e->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_st_e->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			//角度で上下左右を判定
			if ((r < 2 && r >= 0) || r > 358)
			{
				m_st_evx = -0.15f; //右
			}
			if (r > 2 && r < 178)
			{
				m_st_evy = 0.15f;//上
			}
			if (r > 178 && r < 182)
			{
				m_st_evx = 0.15f;//左
			}
			if (r > 182 && r < 358)
			{
				m_st_evy = -0.15f; //下
			}
		}
	}
	if (hit_st_e->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_st_e_death_flg = true; //死亡フラグ
	}	
	if (m_st_e_death_flg == true)
	{
		//爆発オブジェクト作成
		CObjExplosion* obj_bs = new CObjExplosion(hx - 64, hy - 64, m_exp_blood_dst_size, ((UserData*)Save::GetData())->EXP_Attack);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

		m_st_e_death_flg = false;
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
}

//ドロー
void CObjSphere_Type_Enemy::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f;
	src.m_left = 158.0f;
	src.m_right = 190.0f;
	src.m_bottom = 40.0f;
	//描画処理
	dst.m_top = 0.0f + m_st_ey;
	dst.m_left = 0.0f + m_st_ex;
	dst.m_right = m_dst_size + m_st_ex;
	dst.m_bottom = m_dst_size + m_st_ey;

	Draw::Draw(4, &src, &dst, c, 0.0f);
	

}