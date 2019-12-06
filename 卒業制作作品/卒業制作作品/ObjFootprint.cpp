//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjFootprint.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjFootprint::CObjFootprint(float x, float y, float size)
{
	//位置情報登録(数値=位置調整)
	m_bspx = x;
	m_bspy = y;
	//爆発・血しぶき用描画サイズ
	m_exp_blood_dst_size = size;
}

//イニシャライズ
void CObjFootprint::Init()
{
	//初期化
	//アニメーション間隔
	m_ani_time = 0;
	//描画フレーム
	m_ani_flame = 1;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_bspx, m_bspy, m_exp_blood_dst_size, m_exp_blood_dst_size, ELEMENT_WHITE, OBJ_FOOTPRINT, 8);

}

//アクション
void CObjFootprint::Action()
{
	//アニメーション更新
	m_ani_time += 1;

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
void CObjFootprint::Draw()
{
	int Ani_explosion[5] =
	{
		0,1,2,3,4,
	};


	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//足跡用
	RECT_F src_f;
	RECT_F dst_f;
	//切り取り処理
	src_f.m_top = 7.0f + m_UDani_frame * 16.0f;
	src_f.m_left = 145.0f + LRAniData[m_LRani_frame] * 24.0f;
	src_f.m_right = 168.0f + LRAniData[m_LRani_frame] * 24.0f;
	src_f.m_bottom = 34.0f + m_UDani_frame * 16.0f;
	//描画処理
	dst_f.m_top = 0.0f + m_y;
	dst_f.m_left = 0.0f + m_x;
	dst_f.m_right = m_dst_size + m_x;
	dst_f.m_bottom = m_dst_size + m_y;

	//足跡をつける
	Draw::Draw(8, &src_f, &dst_f, c, 0.0f);



}