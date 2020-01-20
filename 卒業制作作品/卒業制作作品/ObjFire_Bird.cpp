//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjFire_Bird.h"

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
CObjFire_Bird::CObjFire_Bird(float fbx, float fby)
{
	//位置情報登録(数値=位置調整)
	m_fbx = fbx;
	m_fby = fby;
}

//イニシャライズ
void CObjFire_Bird::Init()
{
	//初期化
	//移動ベクトル
	m_fbvx = 0.0f;
	m_fbvy = 0.0f;

	//体力
	m_hero_hp = 1;

	//移動ベクトル最大値
	m_fbv_max = 2.5f;

	m_ani_time = 0; //アニメーションフレーム動作間隔
	m_UDani_frame = 2; //静止フレームを初期にする
	m_LRani_frame = 1; //静止フレームを初期にする

	//移動フラグ
	m_fb_x_flg = false;
	m_fb_y_flg = false;

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
	m_fb_death_time = 0; //死亡タイム
	m_fb_death_time_max = 600; //死亡タイム最大値 10秒
	m_fb_Flashing_time = 0; //点滅タイム
	m_fb_Flashing_flg = false; //点滅フラグ

	//ダメージ
	//耐久力フラグがオンの時
	if (En_flg == true)
	{
		m_EXPDameg_num = 25; //爆発ダメージ
	}
	//体力フラグがオンの時
	if (Hp_flg == true)
	{
		m_EXPDameg_num = 50; //爆発ダメージ
	}

	//描画サイズ
	m_dst_size = 96.0f;
	//当たり判定サイズ
	Hitbox_size = 128;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 160;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_fbx, m_fby, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_FIRE_BIRD, 4);
}

//アクション
void CObjFire_Bird::Action()
{
	//上下左右別当たり判定確認フラグ初期化
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_RightHit_flg = false; //右

	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX() - 16; //位置
	float hy = hero->GetY() - 24;
	float hvx = hero->GetVX(); //移動ベクトル
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_fbx; //位置更新
	float hpy = hero->GetPY() - m_fby;
	float h_HitBox = hero->GetHitBox(); //当たり判定
	bool h_gel = hero->GetDel(); //削除チェック

	//ボス
	CObjBoss* boss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);

	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();

	//アイテムドロップ情報取得
	CObjAitemDrop* AitemDrop = (CObjAitemDrop*)Objs::GetObj(OBJ_AITEMDROP);

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false && Eve_Ins == 0)
	{
		//死亡タイム更新
		m_fb_death_time++;

		//移動処理
		//主人公が上に居ると上に移動
		if (hy < m_fby)
		{
			m_fbvy = -m_fbv_max;
			m_ani_time += 1;
			m_UDani_frame = 0;
		}
		//主人公が下に居ると下移動
		else if (hy > m_fby)
		{
			m_fbvy = m_fbv_max;
			m_ani_time += 1;
			m_UDani_frame = 2;
		}
		//主人公が左に居ると左に移動
		if (hx < m_fbx)
		{
			m_fbvx = -m_fbv_max;
			m_ani_time += 1;
			m_UDani_frame = 3;
		}
		//主人公が右に居ると右に移動
		else if (hx > m_fbx)
		{
			m_fbvx = m_fbv_max;
			m_ani_time += 1;			
			m_UDani_frame = 1;
		}
		if (hx == m_fbx)
		{
			m_fbvx = 0.0f;
			m_ani_time += 1;
			//主人公が上に居ると上に移動
			if (hy < m_fby)
			{
				m_fbvy = -m_fbv_max;
				m_UDani_frame = 0;
			}
			//主人公が下に居ると下移動
			else if (hy > m_fby)
			{
				m_fbvy = m_fbv_max;
				m_UDani_frame = 2;
			}
		}
		else if (hy == m_fby)
		{
			m_fbvy = 0.0f;
			m_ani_time += 1;
			//主人公が左に居ると左に移動
			if (hx < m_fbx)
			{
				m_fbvx = -m_fbv_max;
				m_UDani_frame = 3;
			}
			//主人公が右に居ると右に移動
			else if (hx > m_fbx)
			{
				m_fbvx = m_fbv_max;				
				m_UDani_frame = 1;
			}
		}

		//斜め移動修正処理
		float r = 0.0f;
		r = m_fbvx * m_fbvx + m_fbvy * m_fbvy;
		r = sqrt(r); //ルートを求める

		//斜めベクトルを求める
		if (r == 0.0f)
		{
			; //0なら何もしない
		}
		else
		{
			m_fbvx = m_fbv_max / r * m_fbvx;
			m_fbvy = m_fbv_max / r * m_fbvy;
		}

		//位置更新
		//主人公の移動を適応する
		m_fbx += (-hvx) + m_fbvx;
		m_fby += (-hvy) + m_fbvy;

		//アニメーション処理
		if (m_ani_time > 12)
		{
			m_LRani_frame += 1;
			m_ani_time = 0;
		}

		if (m_LRani_frame == 3)
		{
			m_LRani_frame = 0;
		}
	}

	//HitBoxの内容を更新
	CHitBox* hit_fb = Hits::GetHitBox(this); //当たり判定情報取得
	hit_fb->SetPos(m_fbx - 16, m_fby); //当たり判定の位置更新

	//当たり判定処理
	if (hit_fb->CheckElementHit(ELEMENT_WALL) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_fb->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_fb->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//角度で上下左右を判定
				if ((r < 88 && r >= 0) || r > 292)
				{
					m_fbvx = -0.15f; //右
				}
				if (r > 88 && r < 92)
				{
					m_fbvy = 0.15f;//上
				}
				if (r > 92 && r < 268)
				{
					m_fbvx = 0.15f;//左
				}
				if (r > 268 && r < 292)
				{
					m_fbvy = -0.15f; //下
				}
			}
		}
	}

	//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
	if (hit_fb->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_fb->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_fb->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//角度で上下左右を判定
				if ((r < 2 && r >= 0) || r > 358)
				{
					m_fbvx = -0.15f; //右
				}
				if (r > 2 && r < 178)
				{
					m_fbvy = 0.15f;//上
				}
				if (r > 178 && r < 182)
				{
					m_fbvx = 0.15f;//左
				}
				if (r > 182 && r < 358)
				{
					m_fbvy = -0.15f; //下
				}
			}
		}
	}

	if (m_fb_death_time >= 420)
	{
		m_fb_Flashing_flg = true;
	}	
	if (m_fb_death_time >= m_fb_death_time_max)
	{
		m_hero_hp = 0;
	}
	if (m_fb_Flashing_flg == true)
	{
		m_fb_Flashing_time++;
		if (m_fb_Flashing_time >= 60)
		{
			m_fb_Flashing_time = 0;
		}
		if (m_fb_Flashing_time == 40)
		{
			Audio::Start(21);
		}
	}
	if (m_hero_hp <= 0)
	{
		boss->SetFBR(1);

		//爆発オブジェクト作成
		CObjExplosion* obj_bs = new CObjExplosion(m_fbx, m_fby, m_exp_blood_dst_size, m_EXPDameg_num);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
		Audio::Start(9);
		m_fb_death_time = 0; //死亡タイム初期化
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
}

//ドロー
void CObjFire_Bird::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

	//モーション
	int LRAniData[3] =
	{
		1,0,2,
	};

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 255.0f + m_UDani_frame * 30.0f;
	src.m_left = 0.0f + LRAniData[m_LRani_frame] * 25.0f;
	src.m_right = 25.0f + LRAniData[m_LRani_frame] * 25.0f;
	src.m_bottom = 285.0f + m_UDani_frame * 30.0f;
	//描画処理
	dst.m_top = 0.0f + m_fby;
	dst.m_left = 0.0f + m_fbx;
	dst.m_right = m_dst_size + m_fbx;
	dst.m_bottom = m_dst_size + m_fby;

	if (m_fb_Flashing_time >= 40) {
		Draw::Draw(4, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	
}