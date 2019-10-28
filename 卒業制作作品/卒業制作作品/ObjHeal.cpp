//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHeal.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjHeal::CObjHeal(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Genx = 100;
	m_Geny = 100;

}

//イニシャライズ
void CObjHeal::Init()
{
	//初期化
	//発電機起動フラグ
	m_Gen_flg = false;

	//描画サイズ
	m_dst_size = 50.0f;
	//当たり判定サイズ
	Hitbox_size = 50;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Genx, m_Geny, 29, 27, ELEMENT_FIELD, OBJ_APPARATUS, 7);

}

//アクション
void CObjHeal::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//主人公の移動に合わせる
	m_Genx -= hvx;
	m_Geny -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_Genx + 55, m_Geny + 55); //当たり判定の位置更新

}

//ドロー
void CObjHeal::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 7.0f;
	src.m_left = 250.0f;
	src.m_right = 270.0f;
	src.m_bottom = 24.0f;

	//描画処理
	dst.m_top = 85.0f + m_Geny;
	dst.m_left = 85.0f + m_Genx;
	dst.m_right = m_dst_size + m_Genx;
	dst.m_bottom = m_dst_size + m_Geny;
	Draw::Draw(8, &src, &dst, c, 0.0f);
}