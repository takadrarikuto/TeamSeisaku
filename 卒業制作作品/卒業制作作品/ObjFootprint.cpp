//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjFootprint.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CObjFootprint::CObjFootprint(float x, float y,float r)
{
	//位置情報登録(数値=位置調整)
	m_Fx = x;
	m_Fy = y;
	//描画回転
	m_r = r;
}

//イニシャライズ
void CObjFootprint::Init()
{
	//初期化
	//描画フレーム
	m_ani_flame = 1;
	//オブジェクト削除タイム
	m_Delete_time = 150; 

	m_dst_size = 24.0f; //描画サイズ

	m_HitBox_x = 24; //x当たり判定サイズ
	m_HitBox_y = 24; // 当たり判定サイズ

}

//アクション
void CObjFootprint::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//オブジェクト削除
		m_Delete_time--;
	}

	//主人公の移動に合わせる
	m_Fx -= hvx;
	m_Fy -= hvy;

	//HitBoxの内容を更新 
	//CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	//hit_exp->SetPos(m_Fx, m_Fy); //当たり判定の位置更新

	////描画フレームが5になるとSE発生
	//描画フレームが5になるとアニメーション間隔初期化、オブジェクト破棄
	if (m_Delete_time <= 0)
	{
		m_Delete_time = 300;

		this->SetStatus(false); //オブジェクト破棄
	}

}

//ドロー
void CObjFootprint::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//足跡用
	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 160.0f;
	src.m_left = 160.0f;
	src.m_right = 174.0f;
	src.m_bottom = 174.0f;
	//描画処理
	dst.m_top = 0.0f + m_Fy;
	dst.m_left = 0.0f + m_Fx;
	dst.m_right = m_dst_size + m_Fx;
	dst.m_bottom = m_dst_size + m_Fy;

	Draw::Draw(8, &src, &dst, c, m_r);



}