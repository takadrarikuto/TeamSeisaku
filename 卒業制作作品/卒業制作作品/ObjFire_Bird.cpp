//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjFire_Bird.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//メニューキー制御用フラグ
extern bool m_key_flag_menu;

//コンストラクタ
CObjFire_Bird::CObjFire_Bird(float zex, float zey)
{
	//位置情報登録(数値=位置調整)
	m_zex = zex;
	m_zey = zey;
}

//イニシャライズ
void CObjFire_Bird::Init()
{
	//初期化
	//ゾンビ生成位置記録
	m_zeg_x = m_zex;
	m_zeg_y = m_zey;

	//移動ベクトル
	m_zevx = 0.0f;
	m_zevy = 0.0f;

	//体力
	m_hero_hp = 50;

	//移動ベクトル最大値
	m_zev_max = 0.0f;

	m_ani_time = 0; //アニメーションフレーム動作間隔
	m_UDani_frame = 2; //静止フレームを初期にする
	m_LRani_frame = 1; //静止フレームを初期にする

	//移動フラグ
	m_ze_x_flg = false;
	m_ze_y_flg = false;

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

	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 64;

	//ダメージ量
	m_damage = 5;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_zex, m_zey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_ENEMY, 4);
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
	float hx = hero->GetX(); //位置
	float hy = hero->GetY();
	float hvx = hero->GetVX(); //移動ベクトル
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_zex; //位置更新
	float hpy = hero->GetPY() - m_zey;
	float h_HitBox = hero->GetHitBox(); //当たり判定
	bool h_gel = hero->GetDel(); //削除チェック


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
		////計算頻度を落とし、斜め移動を防ぐ
		//static int   count = 20;
		//static float br = 0.0f;
		//count++;
		//if (count > 20)
		//{
		//	count = 0;
		//	int ar = atan2(hpy, hpx)*180.0f / 3.14;

		//	if (ar < 0)
		//	{
		//		ar = 360 + ar;
		//	}
		//	br = ar;
		//}

		//if (br >= 45 && br < 136)//上 45度以上　136度未満
		//{
		//	m_UDani_frame = 6;		
		//}
		//else if (br > 0 && br < 45 || br >= 315) //右　0度以上かつ45度未満　315度以上
		//{			
		//	m_UDani_frame = 4;
		//}
		//else if (br > 225 && br < 316)//下　225度以上　316未満
		//{			
		//	m_UDani_frame = 2;
		//}
		//else if (br >= 135 && br <= 225)//左　135度以上　225度未満
		//{
		//	m_UDani_frame = 0;
		//}

		//移動処理
		//主人公が上に居ると上に移動
		if (hy < m_zey)
		{
			m_zevy = -m_zev_max;
			m_ani_time += 1;
			m_UDani_frame = 6;
		}
		//主人公が下に居ると下移動
		else if (hy > m_zey)
		{
			m_zevy = m_zev_max;
			m_ani_time += 1;
			m_UDani_frame = 2;
		}
		//主人公が左に居ると左に移動
		if (hx < m_zex)
		{
			m_zevx = -m_zev_max;
			m_ani_time += 1;
			m_UDani_frame = 0;
		}
		//主人公が右に居ると右に移動
		else if (hx > m_zex)
		{
			m_zevx = m_zev_max;
			m_ani_time += 1;
			m_UDani_frame = 4;
		}
		if (hx == m_zex)
		{
			m_zevx = 0.0f;
			m_ani_time += 1;
			//主人公が上に居ると上に移動
			if (hy < m_zey)
			{
				m_zevy = -m_zev_max;
				m_UDani_frame = 6;
			}
			//主人公が下に居ると下移動
			else if (hy > m_zey)
			{
				m_zevy = m_zev_max;
				m_UDani_frame = 2;
			}
		}
		else if (hy == m_zey)
		{
			m_zevy = 0.0f;
			m_ani_time += 1;
			//主人公が左に居ると左に移動
			if (hx < m_zex)
			{
				m_zevx = -m_zev_max;
				m_UDani_frame = 0;
			}
			//主人公が右に居ると右に移動
			else if (hx > m_zex)
			{
				m_zevx = m_zev_max;
				m_UDani_frame = 4;
			}
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

		//位置更新
		//主人公の移動を適応する
		//m_zex -= hvx;
		//m_zey -= hvy;
		m_zex += (-hvx) + m_zevx;
		m_zey += (-hvy) + m_zevy;

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
	hit_ze->SetPos(m_zex, m_zey); //当たり判定の位置更新

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
				m_zevx = -0.15f; //右
			}
			if (r > 88 && r < 92)
			{
				m_zevy = 0.15f;//上
			}
			if (r > 92 && r < 268)
			{
				m_zevx = 0.15f;//左
			}
			if (r > 268 && r < 292)
			{
				m_zevy = -0.15f; //下
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
				m_zevx = -0.15f; //右
			}
			if (r > 2 && r < 178)
			{
				m_zevy = 0.15f;//上
			}
			if (r > 178 && r < 182)
			{
				m_zevx = 0.15f;//左
			}
			if (r > 182 && r < 358)
			{
				m_zevy = -0.15f; //下
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
					m_RightHit_flg = true; //右
					m_zevx = m_zevx - m_zev_max;
				}
				else if (r > 2 && r < 178)
				{
					m_UpHit_flg = true;    //上
					m_zevy = m_zevy + m_zev_max;
				}
				else if (r > 176 && r < 184)
				{
					m_LeftHit_flg = true;	 //左
					m_zevx = m_zevx + m_zev_max;
				}
				else if (r > 182 && r < 358)
				{
					m_DownHit_flg = true;	 //下
					m_zevy = m_zevy - m_zev_max;
				}
			}
		}
	}

	//敵機・敵弾・トラップ系オブジェクトと接触したら主人公機無敵時間開始
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

	if (m_hero_hp <= 0)
	{
		//血しぶきオブジェクト作成
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_zex, m_zey, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);

		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
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
	src.m_top = 130.0f + m_UDani_frame * 16.0f;
	src.m_left = 0.0f + LRAniData[m_LRani_frame] * 25.0f;
	src.m_right = 24.0f + LRAniData[m_LRani_frame] * 25.0f;
	src.m_bottom = 160.0f + m_UDani_frame * 16.0f;
	//描画処理
	dst.m_top = 0.0f + m_zey;
	dst.m_left = 0.0f + m_zex;
	dst.m_right = m_dst_size + m_zex;
	dst.m_bottom = m_dst_size + m_zey;

	Draw::Draw(4, &src, &dst, c, 0.0f);
	
}