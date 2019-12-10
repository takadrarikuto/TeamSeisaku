//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBarbedWireSmall.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBarbedWireSmall::CObjBarbedWireSmall(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_BarbedSx = x;
	m_BarbedSy = y;
}

//イニシャライズ
void CObjBarbedWireSmall::Init()
{
	//初期化
	//描画サイズ
	m_dst_size = 50.0f;
	//XY当たり判定サイズ
	m_XHitbox_size = 68;
	m_YHitbox_size = 53;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_BarbedSx, m_BarbedSy, m_XHitbox_size, m_YHitbox_size, ELEMENT_MAGIC, OBJ_BARBED_WIRE_SMALL, 7);
}

//アクション
void CObjBarbedWireSmall::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//主人公の移動に合わせる
	m_BarbedSx -= hvx;
	m_BarbedSy -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_BarbedSx + 1, m_BarbedSy + 1); //当たり判定の位置更新
}

//ドロー
void CObjBarbedWireSmall::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//1
	//切り取り処理
	src.m_top = 149.0f;
	src.m_left = 149.0f;
	src.m_right = 182.0f;
	src.m_bottom = 182.0f;

	//描画処理(34*34)
	dst.m_top = 0.0f + m_BarbedSy;
	dst.m_left = 0.0f + m_BarbedSx;
	dst.m_right = 68.0f + m_BarbedSx;
	dst.m_bottom = 53.0f + m_BarbedSy;
	Draw::Draw(7, &src, &dst, c, 0.0f);

	////2
	////切り取り処理
	//src.m_top = 151.0f;
	//src.m_left = 189.0f;
	//src.m_right = 222.0f;
	//src.m_bottom = 184.0f;

	////描画処理(34*34)
	//dst.m_top = 0.0f + m_BarbedSy;
	//dst.m_left = 0.0f + m_BarbedSx;
	//dst.m_right = 68.0f + m_BarbedSx;
	//dst.m_bottom = 53.0f + m_BarbedSy;
	//Draw::Draw(7, &src, &dst, c, 0.0f);

	////3
	////切り取り処理
	//src.m_top = 185.0f;
	//src.m_left = 149.0f;
	//src.m_right = 182.0f;
	//src.m_bottom = 212.0f;

	////描画処理(34*34)
	//dst.m_top = 0.0f + m_BarbedSy;
	//dst.m_left = 0.0f + m_BarbedSx;
	//dst.m_right = 68.0f + m_BarbedSx;
	//dst.m_bottom = 53.0f + m_BarbedSy;
	//Draw::Draw(7, &src, &dst, c, 0.0f);
}