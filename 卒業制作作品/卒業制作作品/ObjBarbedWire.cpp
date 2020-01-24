//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBarbedWire.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBarbedWire::CObjBarbedWire(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Barbedx = x;
	m_Barbedy = y;

}

//イニシャライズ
void CObjBarbedWire::Init()
{
	//初期化
	//XY当たり判定サイズ
	m_XHitbox_size = 101;
	m_YHitbox_size = 72;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Barbedx, m_Barbedy, m_XHitbox_size, m_YHitbox_size, ELEMENT_BARBED_S, OBJ_BARBED_WIRE, 7);
}

//アクション
void CObjBarbedWire::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//主人公の移動に合わせる
	m_Barbedx -= hvx;
	m_Barbedy -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_Barbedx + 1, m_Barbedy + 1); //当たり判定の位置更新
}

//ドロー
void CObjBarbedWire::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 150.0f;
	src.m_left = 10.0f;
	src.m_right = 60.0f;
	src.m_bottom = 181.0f;

	//描画処理(101*36)
	dst.m_top = 0.0f + m_Barbedy;
	dst.m_left = 0.0f + m_Barbedx;
	dst.m_right = 101.0f + m_Barbedx;
	dst.m_bottom = 72.0f + m_Barbedy;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}