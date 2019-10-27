//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjZombieEnemy.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//メニューキー制御用フラグ
extern bool m_key_flag_menu;

//コンストラクタ
CObjZombieEnemy::CObjZombieEnemy(float zex, float zey, bool zeaf)
{
	//位置情報登録(数値=位置調整)
	m_zex = zex;
	m_zey = zey;
	//エネミー描画フレーム切り替えフラグ取得用
	m_ani_frame_flg = zeaf;
}

//イニシャライズ
void CObjZombieEnemy::Init()
{
	//初期化
	//移動ベクトル
	m_zevx = 0.0f;
	m_zevy = 0.0f;

	//体力
	m_hero_hp = 50;

	//移動ベクトル最大値
	m_zev_max = 0.0f;

	m_ani_time = 0; //アニメーションフレーム動作間隔
	m_UDani_frame = 4; //静止フレームを初期にする
	m_LRani_frame = 1; //静止フレームを初期にする

	//攻撃頻度
	m_at = 0;
	//攻撃頻度最大値
	m_at_max = 5;
	//ダメージ量
	Gun_Attack = 10;  //ハンドガン
	SHG_Attack = 30;  //ショットガン
	AR_Attack = 20;	  //アサルトライフル
	SR_Attack = 50;	  //スナイパーライフル
	RL_Attack = 150;  //ロケットランチャー
	RG_Attack = 200;  //レールガン
	GRE_Attack = 100; //グレネード


	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 64;

	//ダメージ量
	m_damage = 5;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_zex, m_zey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_ENEMY, 5);
}

//アクション
void CObjZombieEnemy::Action()
{
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();
	//爆発
	CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
	int EXPDamage;
	if (EXPAttack != nullptr)
	{
		EXPDamage = EXPAttack->GetEXP();
	}

	if (m_ani_frame_flg == true)
	{
		m_zev_max = 1.5f;
	}
	//直立状態
	else if (m_ani_frame_flg == false)
	{
		m_zev_max = 2.0f;
	}


	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//移動処理
		//主人公の移動を適応する
		m_zevx -= hvx;
		m_zevy -= hvy;

		//主人公が左に居ると左に移動
		if (hx < m_zex)
		{
			m_zevx -= m_zev_max;
			m_UDani_frame = 0;
			m_ani_time += 1;
		}
		//主人公が右に居ると右に移動
		else if (hx > m_zex)
		{
			m_zevx += m_zev_max;
			m_UDani_frame = 4;
			m_ani_time += 1;
		}
		//主人公が上に居ると上に移動
		if (hy < m_zey)
		{
			m_zevy -= m_zev_max;
			m_UDani_frame = 6;
			m_ani_time += 1;
		}
		//主人公が下に居ると下移動
		else if (hy > m_zey)
		{
			m_zevy += m_zev_max;
			m_UDani_frame = 2;
			m_ani_time += 1;
		}
		//主人公とx,y位置が同じだと移動
		if (hx == m_zex)
		{
			m_zevx = 0.0f;
		}
		else if (hy == m_zey)
		{
			m_zevy = 0.0f;
		}
		//斜め移動修正処理
		float r = 0.0f;
		r = m_zevx * m_zevx + m_zevy * m_zevy;
		r = sqrt(r); //ルートを求める

		//斜めベクトルを求める
		if (r == 0.0f)
		{
			; //0なら何もしない
		}
		else
		{
			m_zevx = m_zev_max / r * m_zevx;
			m_zevy = m_zev_max / r * m_zevy;
		}

		
		//アニメーション処理
		if (m_ani_time > 6)
		{
			m_LRani_frame += 1;
			m_ani_time = 0;
		}

		if (m_LRani_frame == 3)
		{
			m_LRani_frame = 0;
		}

		//位置更新
		m_zex += m_zevx;
		m_zey += m_zevy;
	}

	//HitBoxの内容を更新
	CHitBox* hit_ze = Hits::GetHitBox(this); //当たり判定情報取得
	hit_ze->SetPos(m_zex, m_zey); //当たり判定の位置更新
	

	//敵機・敵弾・トラップ系オブジェクトと接触したら主人公機無敵時間開始
	//ハンドガン
	if (hit_ze->CheckObjNameHit(OBJ_GUNATTACK) != nullptr)
	{
		m_hero_hp -= Gun_Attack;
	}
	//ショットガン
	else if (hit_ze->CheckObjNameHit(OBJ_SHOTGUNATTACK) != nullptr)
	{
		m_hero_hp -= SHG_Attack;
	}
	//アサルトライフル
	else if (hit_ze->CheckObjNameHit(OBJ_ARATTACK) != nullptr)
	{
		m_hero_hp -= AR_Attack;
	}
	//スナイパーライフル
	else if (hit_ze->CheckObjNameHit(OBJ_SNIPERRIFLEATTACK) != nullptr)
	{
		m_hero_hp -= SR_Attack;
	}
	//ロケットランチャー
	else if (hit_ze->CheckObjNameHit(OBJ_ROCKETLAUNCHERATTACK) != nullptr)
	{
		m_hero_hp -= RL_Attack;
	}
	//レールガン
	else if (hit_ze->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
	{
		m_hero_hp -= RG_Attack;
	}	
	//グレネード
	else if (hit_ze->CheckObjNameHit(OBJ_GRENADEATTACK) != nullptr)
	{
		m_hero_hp -= GRE_Attack;
	}
	//爆発
	else if (hit_ze->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
	{
		m_hero_hp -= EXPDamage;
	}
	if (m_hero_hp <= 0)
	{
		//血しぶきオブジェクト作成
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_zex, m_zey, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);

		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
}

//ドロー
void CObjZombieEnemy::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//モーション
	int LRAniData[3] =
	{
		1,0,2,
	};

	RECT_F src;
	RECT_F dst;

	//這いずり、立っている描画切り替え
	//這いずり状態
	if (m_ani_frame_flg == true)
	{
		//切り取り処理
		src.m_top = 130.0f + m_UDani_frame * 16.0f;
		src.m_left = 0.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_right = 24.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_bottom = 160.0f + m_UDani_frame * 16.0f;
	}
	//直立状態
	else if (m_ani_frame_flg == false)
	{
		//切り取り処理
		src.m_top = 0.0f + m_UDani_frame * 16.0f;
		src.m_left = 0.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_right = 24.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_bottom = 30.0f + m_UDani_frame * 16.0f;
	}	
	//描画処理
	dst.m_top = 0.0f + m_zey;
	dst.m_left = 0.0f + m_zex;
	dst.m_right = m_dst_size + m_zex;
	dst.m_bottom = m_dst_size + m_zey;
	Draw::Draw(5, &src, &dst, c, 0.0f);


}