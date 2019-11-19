//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjBat_Enemy.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//メニューキー制御用フラグ
extern bool m_key_flag_menu;

//コンストラクタ
CObjBat_Enemy::CObjBat_Enemy(float bex, float bey)
{
	//位置情報登録(数値=位置調整)
	m_bex = bex;
	m_bey = bey;
}

//イニシャライズ
void CObjBat_Enemy::Init()
{
	//初期化
	//移動ベクトル
	m_bevx = 0.0f;
	m_bevy = 0.0f;

	//体力
	m_hero_hp = 10;

	//移動ベクトル最大値
	m_bev_max = 3.0f;

	m_ani_time = 0; //アニメーションフレーム動作間隔
	m_UDani_frame = 2; //静止フレームを初期にする
	m_LRani_frame = 1; //静止フレームを初期にする

	//移動フラグ
	m_be_x_flg = false;
	m_be_y_flg = false;

	//上下左右別当たり判定確認フラグ
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_RightHit_flg = false; //右

	//攻撃頻度
	m_at = 0;
	//攻撃頻度最大値
	m_at_max = 5;

	//ダメージ量
	((UserData*)Save::GetData())->Gun_Attack;
	((UserData*)Save::GetData())->SHG_Attack;
	((UserData*)Save::GetData())->AR_Attack;
	((UserData*)Save::GetData())->SR_Attack;
	((UserData*)Save::GetData())->RL_Attack;
	((UserData*)Save::GetData())->RG_Attack;
	((UserData*)Save::GetData())->GRE_Attack;

	//ダメージ点滅時間用
	m_time_d = 0;

	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 64;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_bex, m_bey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_BAT_ENEMY, 4);
}

//アクション
void CObjBat_Enemy::Action()
{
	//上下左右別当たり判定確認フラグ初期化
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_RightHit_flg = false; //右

	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX(); //位置
	float hy = hero->GetY();
	float hvx = hero->GetVX(); //移動ベクトル
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_bex; //位置更新
	float hpy = hero->GetPY() - m_bey;

	//爆発
	CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
	int EXPDamage;
	if (EXPAttack != nullptr)
	{
		EXPDamage = EXPAttack->GetEXP();
	}

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//移動処理	
		m_ani_time += 1;
		//主人公が上に居ると上に移動
		if (hy < m_bey)
		{
			m_bevy = -m_bev_max;
			m_ani_time += 1;
			m_UDani_frame = 0;
		}
		//主人公が下に居ると下移動
		else if (hy > m_bey)
		{
			m_bevy = m_bev_max;
			m_ani_time += 1;
			m_UDani_frame = 2;
		}
		//主人公が左に居ると左に移動
		if (hx < m_bex)
		{
			m_bevx = -m_bev_max;
			m_ani_time += 1;
			m_UDani_frame = 3;
		}
		//主人公が右に居ると右に移動
		else if (hx > m_bex)
		{
			m_bevx = m_bev_max;
			m_ani_time += 1;
			m_UDani_frame = 1;
		}
		if (hx == m_bex)
		{
			m_bevx = 0.0f;
			m_ani_time += 1;
			//主人公が上に居ると上に移動
			if (hy < m_bey)
			{
				m_bevy = -m_bev_max;
				m_UDani_frame = 0;
			}
			//主人公が下に居ると下移動
			else if (hy > m_bey)
			{
				m_bevy = m_bev_max;
				m_UDani_frame = 2;
			}
		}
		else if (hy == m_bey)
		{
			m_bevy = 0.0f;
			m_ani_time += 1;
			//主人公が左に居ると左に移動
			if (hx < m_bex)
			{
				m_bevx = -m_bev_max;
				m_UDani_frame = 3;
			}
			//主人公が右に居ると右に移動
			else if (hx > m_bex)
			{
				m_bevx = m_bev_max;
				m_UDani_frame = 1;
			}
		}

		//斜め移動修正処理
		float r = 0.0f;
		r = m_bevy * m_bevy + m_bevx * m_bevx;
		r = sqrt(r); //ルートを求める

		//斜めベクトルを求める
		if (r == 0.0f)
		{
			; //0なら何もしない
		}
		else
		{
			m_bevx = m_bev_max / r * m_bevx;
			m_bevy = m_bev_max / r * m_bevy;
		}
		//位置更新
		//主人公の移動を適応する
		m_bex += (-hvx) + m_bevx;
		m_bey += (-hvy) + m_bevy;

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
	}

	//HitBoxの内容を更新
	CHitBox* hit_ze = Hits::GetHitBox(this); //当たり判定情報取得
	hit_ze->SetPos(m_bex, m_bey); //当たり判定の位置更新

								  //当たり判定処理
	if (hit_ze->CheckElementHit(ELEMENT_WALL) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_ze->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_ze->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			//角度で上下左右を判定
			if ((r < 88 && r >= 0) || r > 292)
			{
				m_bevx = -0.15f; //右
			}
			if (r > 88 && r < 92)
			{
				m_bevy = 0.15f;//上
			}
			if (r > 92 && r < 268)
			{
				m_bevx = 0.15f;//左
			}
			if (r > 268 && r < 292)
			{
				m_bevy = -0.15f; //下
			}
		}
	}

	//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
	if (hit_ze->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_ze->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_ze->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			//角度で上下左右を判定
			if ((r < 2 && r >= 0) || r > 358)
			{
				m_bevx = -0.15f; //右
			}
			if (r > 2 && r < 178)
			{
				m_bevy = 0.15f;//上
			}
			if (r > 178 && r < 182)
			{
				m_bevx = 0.15f;//左
			}
			if (r > 182 && r < 358)
			{
				m_bevy = -0.15f; //下
			}
		}
	}

	//敵がステージの当たり判定に当たった時の処理（全ステージ対応）
	if (hit_ze->CheckElementHit(ELEMENT_FIELD) == true)
	{
		HIT_DATA** hit_data;
		hit_data = hit_ze->SearchElementHit(ELEMENT_FIELD);

		float r = 0;

		for (int i = 0; i < 10; i++)
		{
			if (hit_data[i] != nullptr)
			{
				r = hit_data[i]->r;

				//角度で上下左右を判定
				if ((r < 4 && r >= 0) || r > 356)
				{
					m_bevx = m_bevx - m_bev_max;
				}
				else if (r > 2 && r < 178)
				{
					m_bevy = m_bevy + m_bev_max;
				}
				else if (r > 176 && r < 184)
				{
					m_bevx = m_bevx + m_bev_max;
				}
				else if (r > 182 && r < 358)
				{
					m_bevy = m_bevy - m_bev_max;
				}
			}
		}
	}

	//主人公弾・爆発オブジェクトと接触したら敵ダメージ、無敵時間開始
	//ハンドガン
	if (hit_ze->CheckObjNameHit(OBJ_GUNATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->Gun_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//ショットガン
	else if (hit_ze->CheckObjNameHit(OBJ_SHOTGUNATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->SHG_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//アサルトライフル
	else if (hit_ze->CheckObjNameHit(OBJ_ARATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->AR_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//スナイパーライフル
	else if (hit_ze->CheckObjNameHit(OBJ_SNIPERRIFLEATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->SR_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//ロケットランチャー
	else if (hit_ze->CheckObjNameHit(OBJ_ROCKETLAUNCHERATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->RL_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//レールガン
	else if (hit_ze->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->RG_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//グレネード
	else if (hit_ze->CheckObjNameHit(OBJ_GRENADEATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->GRE_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//爆発
	else if (hit_ze->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
	{
		m_hero_hp -= EXPDamage;
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}

	if (m_hero_hp <= 0)
	{
		//血しぶきオブジェクト作成
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_bex, m_bey, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);

		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
}

//ドロー
void CObjBat_Enemy::Draw()
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
	src.m_top = 135.0f + m_UDani_frame * 32.0f;
	src.m_left = 74.4f + LRAniData[m_LRani_frame] * 24.8f;
	src.m_right = 98.0f + LRAniData[m_LRani_frame] * 24.8f;
	src.m_bottom = 170.0f + m_UDani_frame * 32.0f;
	//描画処理
	dst.m_top = 0.0f + m_bey;
	dst.m_left = 0.0f + m_bex;
	dst.m_right = m_dst_size + m_bex;
	dst.m_bottom = m_dst_size + m_bey;

	if (m_time_d > 0) {
		Draw::Draw(4, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}

}