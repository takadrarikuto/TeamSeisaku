//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjExplosion.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CObjExplosion::CObjExplosion(float x, float y, float size, int Damage)
{
	//位置情報登録(数値=位置調整)
	m_Expx = x;
	m_Expy = y;
	//描画・当たり判定範囲
	m_exp_blood_dst_size = size;
	//爆発ダメージ
	m_Exp_Damage = Damage;
}

//イニシャライズ
void CObjExplosion::Init()
{
	//初期化
	//アニメーション間隔
	m_ani_time = 0;
	//描画フレーム
	m_ani_flame = 1;
	//上下移動描画フレーム
	m_UDani_flame = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Expx, m_Expy, m_exp_blood_dst_size, m_exp_blood_dst_size, ELEMENT_MAGIC, OBJ_EXPLOSION, 9);

}

//アクション
void CObjExplosion::Action()
{
	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//主人公位置取得
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float hvx = hero->GetVX();
		float hvy = hero->GetVY();

		//主人公の移動に合わせる
		m_Expx -= hvx;
		m_Expy -= hvy;

		//アニメーション更新
		m_ani_time += 1;

		//アニメーション処理
		if (m_ani_time > 5)
		{
			m_ani_flame += 1;
			m_ani_time = 0;
		}

		//HitBoxの内容を更新 
		CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
		hit_exp->SetPos(m_Expx, m_Expy); //当たり判定の位置更新


		////描画フレームが5になるとSE発生
		//描画フレームが5になるとアニメーション間隔初期化、オブジェクト破棄
		if (m_UDani_flame == 0 && m_ani_flame == 8)
		{
			m_UDani_flame = 1;
			m_ani_flame = 0;
		}
		else if (m_UDani_flame == 1 && m_ani_flame == 6)
		{
			m_ani_flame = 0;

			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
	}
}

//ドロー
void CObjExplosion::Draw()
{
	int Ani_explosion[8] =
	{
		0,1,2,3,4,5,6,7,
	};


	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f + m_UDani_flame * 100;
	src.m_left = 0.0f + Ani_explosion[m_ani_flame] * 96;
	src.m_right = 100.0f + Ani_explosion[m_ani_flame] * 96;
	src.m_bottom = 100.0f + m_UDani_flame * 100;

	//描画処理
	dst.m_top = 0.0f + m_Expy;
	dst.m_left = 0.0f + m_Expx;
	dst.m_right = m_exp_blood_dst_size + m_Expx;
	dst.m_bottom = m_exp_blood_dst_size + m_Expy;
	Draw::Draw(9, &src, &dst, c, 0.0f);



}