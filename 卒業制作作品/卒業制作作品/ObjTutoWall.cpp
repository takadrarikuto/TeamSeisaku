//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTutoWall.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjTutoWall::CObjTutoWall(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Wallx = 0 - 50;
	m_Wally = 0;

}

//イニシャライズ
void CObjTutoWall::Init()
{
	//初期化
	//描画サイズ
	m_dst_size = 50.0f;
	//XY当たり判定サイズ
	m_XHitbox_size = 50;
	m_YHitbox_size = 600;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Wallx, m_Wally, m_XHitbox_size, m_YHitbox_size, ELEMENT_WALL, OBJ_WALL, 7);

}

//アクション
void CObjTutoWall::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_TUTO_HERO);
	float hvx;
	float hvy;
	if (hero != nullptr)
	{
		hvx = hero->GetVX();
		hvy = hero->GetVY();
	}

	//主人公の移動に合わせる
	m_Wallx -= hvx;
	m_Wally -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_Wallx + 1, m_Wally + 1); //当たり判定の位置更新
}

//ドロー
void CObjTutoWall::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//描画処理
	dst.m_top = 0.0f + m_Wally;
	dst.m_left = 0.0f + m_Wallx;
	dst.m_right = 50.0f + m_Wallx;
	dst.m_bottom = 600.0f + m_Wally;
	Draw::Draw(31, &src, &dst, c, 0.0f);
}