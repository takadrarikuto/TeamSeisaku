//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjMeme_Medium_Boss.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjMeme_Medium_Boss::CObjMeme_Medium_Boss(float mmbx, float mmby)
{
	//位置情報登録(数値=位置調整)
	m_mmbx = mmbx;
	m_mmby = mmby;
}

//イニシャライズ
void CObjMeme_Medium_Boss::Init()
{
	//初期化	
	//移動ベクトル
	m_mmbvx = 0.0f;
	m_mmbvy = 0.0f;
	//体力
	m_hero_hp = 1;

	//移動ベクトル最大値
	m_mmbv_max = 2.0f;

	m_ani_time = 0; //アニメーションフレーム動作間隔
	m_UDani_frame = 0; //静止フレームを初期にする
	m_LRani_frame = 1; //静止フレームを初期にする

	//上下左右別当たり判定確認フラグ
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_RightHit_flg = false; //右

	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_mmbx, m_mmby, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_MEME_MEDIUM_BOSS, 4);
}

//アクション
void CObjMeme_Medium_Boss::Action()
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
	float hpx = hero->GetPX() - m_mmbx; //位置更新
	float hpy = hero->GetPY() - m_mmby;
	float h_HitBox = hero->GetHitBox(); //当たり判定
	bool h_gel = hero->GetDel(); //削除チェック

	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();

	//ミーム実態無力化装置情報取得
	CObjMeme_Neutralization_Device* MND = (CObjMeme_Neutralization_Device*)Objs::GetObj(OBJ_MEME_NEUTRALIZATION_DEVICE);
	bool Meme_death = MND->GetMeme_death();

	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg;
	if (Menu != nullptr)
	{
		Menu_flg = Menu->GetMenu();
	}

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false && Eve_Ins == 0)
	{
		//移動処理
		//主人公が上に居ると上に移動
		if (hy < m_mmby)
		{
			m_mmbvy = -m_mmbv_max;
			m_ani_time += 1;
		}
		//主人公が下に居ると下移動
		else if (hy > m_mmby)
		{
			m_mmbvy = m_mmbv_max;
			m_ani_time += 1;
		}
		//主人公が左に居ると左に移動
		if (hx < m_mmbx)
		{
			m_mmbvx = -m_mmbv_max;
			m_ani_time += 1;
		}
		//主人公が右に居ると右に移動
		else if (hx > m_mmbx)
		{
			m_mmbvx = m_mmbv_max;
			m_ani_time += 1;
		}
		if (hx == m_mmbx)
		{
			m_mmbvx = 0.0f;
			m_ani_time += 1;
			//主人公が上に居ると上に移動
			if (hy < m_mmby)
			{
				m_mmbvy = -m_mmbv_max;
			}
			//主人公が下に居ると下移動
			else if (hy > m_mmby)
			{
				m_mmbvy = m_mmbv_max;
			}
		}
		else if (hy == m_mmby)
		{
			m_mmbvy = 0.0f;
			m_ani_time += 1;
			//主人公が左に居ると左に移動
			if (hx < m_mmbx)
			{
				m_mmbvx = -m_mmbv_max;
			}
			//主人公が右に居ると右に移動
			else if (hx > m_mmbx)
			{
				m_mmbvx = m_mmbv_max;
			}
		}

		//斜め移動修正処理
		float r = 0.0f;
		r = m_mmbvx * m_mmbvx + m_mmbvy * m_mmbvy;
		r = sqrt(r); //ルートを求める

		//斜めベクトルを求める
		if (r == 0.0f)
		{
			; //0なら何もしない
		}
		else
		{
			m_mmbvx = m_mmbv_max / r * m_mmbvx;
			m_mmbvy = m_mmbv_max / r * m_mmbvy;
		}

		//位置更新
		//主人公の移動を適応する
		m_mmbx += (-hvx) + m_mmbvx;
		m_mmby += (-hvy) + m_mmbvy;

		//アニメーション処理
		if (m_ani_time > 6)
		{
			m_LRani_frame += 1;
			m_ani_time = 0;
		}

		//左右
		if (m_LRani_frame > 5)
		{
			m_LRani_frame = 0;
			m_UDani_frame = 1;
		}

		//上下
		if (m_UDani_frame > 1)
		{
			m_UDani_frame = 0;
		}
	}

	//HitBoxの内容を更新
	CHitBox* hit_mmb = Hits::GetHitBox(this); //当たり判定情報取得
	hit_mmb->SetPos(m_mmbx, m_mmby); //当たり判定の位置更新

	//当たり判定処理
	if (hit_mmb->CheckElementHit(ELEMENT_WALL) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_mmb->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_mmb->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//角度で上下左右を判定
				if ((r < 88 && r >= 0) || r > 292)
				{
					m_mmbvx = -0.15f; //右
				}
				if (r > 88 && r < 92)
				{
					m_mmbvy = 0.15f;//上
				}
				if (r > 92 && r < 268)
				{
					m_mmbvx = 0.15f;//左
				}
				if (r > 268 && r < 292)
				{
					m_mmbvy = -0.15f; //下
				}
			}			
		}
	}

	//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
	if (hit_mmb->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_mmb->SearchElementHit(ELEMENT_WALL2);		
		for (int i = 0; i < hit_mmb->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//角度で上下左右を判定
				if ((r < 2 && r >= 0) || r > 358)
				{
					m_mmbvx = -0.15f; //右
				}
				if (r > 2 && r < 178)
				{
					m_mmbvy = 0.15f;//上
				}
				if (r > 178 && r < 182)
				{
					m_mmbvx = 0.15f;//左
				}
				if (r > 182 && r < 358)
				{
					m_mmbvy = -0.15f; //下
				}
			}		
		}
	}

	if (Meme_death == true)
	{
		Meme_death = false; //死亡判定初期化
		MND->SetMeme_death(Meme_death); //死亡判定操作
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
}

//ドロー
void CObjMeme_Medium_Boss::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//モーション
	int LRAniData[6] =
	{
		0,1,2,3,4,5,
	};

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 10.0f + m_UDani_frame * 64.0f;
	src.m_left = 210.0f + LRAniData[m_LRani_frame] * 65.0f;
	src.m_right = 265.0f + LRAniData[m_LRani_frame] * 65.0f;
	src.m_bottom = 66.0f + m_UDani_frame * 64.0f;
	//描画処理
	dst.m_top = 0.0f + m_mmby;
	dst.m_left = 0.0f + m_mmbx;
	dst.m_right = m_dst_size + m_mmbx;
	dst.m_bottom = m_dst_size + m_mmby;

	Draw::Draw(4, &src, &dst, c, 0.0f);
	

}