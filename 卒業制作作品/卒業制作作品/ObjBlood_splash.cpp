//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjBlood_splash.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CObjBlood_splash::CObjBlood_splash(float x, float y, float size)
{
	//位置情報登録(数値=位置調整)
	m_bspx = x;
	m_bspy = y;
	//爆発・血しぶき用描画サイズ
	m_exp_blood_dst_size = size; 
}

//イニシャライズ
void CObjBlood_splash::Init()
{
	//初期化
	//アニメーション間隔
	m_ani_time = 0;
	//描画フレーム
	m_ani_flame = 1;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_bspx, m_bspy, m_exp_blood_dst_size, m_exp_blood_dst_size, ELEMENT_RED, OBJ_BLOOD_SPLASH, 10);

}

//アクション
void CObjBlood_splash::Action()
{
	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//アニメーション更新
		m_ani_time += 1;
	}
	
	//アニメーション処理
	if (m_ani_time > 5)
	{
		m_ani_flame += 1;
		m_ani_time = 0;
	}

	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//主人公の移動に合わせる
	m_bspx -= hvx;
	m_bspy -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_bspx, m_bspy); //当たり判定の位置更新

	////描画フレームが5になるとSE発生
	//描画フレームが5になるとアニメーション間隔初期化、オブジェクト破棄
	if (m_ani_flame == 1)
	{		
		//if (Exp_flg == true)
		//{
		//	//Audio::Start(4); //音楽スタート
		//	Exp_flg = false;
		//}
		////Boss爆発
		//if (B_Exp_flg == true)
		//{
		//	//Audio::Start(5); //音楽スタート
		//	B_Exp_flg = false;
		//}
	}
	else if (m_ani_flame == 5)
	{
		m_ani_flame = 5;

		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}

}

//ドロー
void CObjBlood_splash::Draw()
{
	int Ani_explosion[5] =
	{
		0,1,2,3,4,
	};


	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f;
	src.m_left = 0.0f + Ani_explosion[m_ani_flame] * 120;
	src.m_right = 120.0f + Ani_explosion[m_ani_flame] * 120;
	src.m_bottom = 120.0f;

	//描画処理
	dst.m_top = 0.0f + m_bspy;
	dst.m_left = 0.0f + m_bspx;
	dst.m_right = m_exp_blood_dst_size + m_bspx;
	dst.m_bottom = m_exp_blood_dst_size + m_bspy;
	Draw::Draw(10, &src, &dst, c, 0.0f);



}