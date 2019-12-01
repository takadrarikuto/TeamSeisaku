//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBarbedWireV.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBarbedWireV::CObjBarbedWireV(float x, float y, bool lr_ch)
{
	//位置情報登録(数値=位置調整)
	m_BarbedVx = x;
	m_BarbedVy = y;
	//左右表示切り替えフラグ
	m_BarbedV_LR_Change_flg = lr_ch;
}

//イニシャライズ
void CObjBarbedWireV::Init()
{
	//初期化
	//XY当たり判定サイズ
	m_XHitbox_size = 72;
	m_YHitbox_size = 131;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_BarbedVx, m_BarbedVy, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_BARBED_WIRE_V, 7);
}

//アクション
void CObjBarbedWireV::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//主人公の移動に合わせる
	m_BarbedVx -= hvx;
	m_BarbedVy -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_BarbedVx + 1, m_BarbedVy + 1); //当たり判定の位置更新
}

//ドロー
void CObjBarbedWireV::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理(左右)
	//右向き
	if (m_BarbedV_LR_Change_flg == true)
	{
		//切り取り処理
		src.m_left = 74.0f;
		src.m_right = 103.0;
	}
	//左向き
	else if (m_BarbedV_LR_Change_flg == false)
	{
		//切り取り処理
		src.m_left = 10.0f;
		src.m_right = 42.0f;
	}
	
	//切り取り処理(上下)
	src.m_top = 205.0f;
	src.m_bottom = 253.0f;

	//描画処理
	dst.m_top = 0.0f + m_BarbedVy;
	dst.m_left = 0.0f + m_BarbedVx;
	dst.m_right = 72.0f + m_BarbedVx;
	dst.m_bottom = 131.0f + m_BarbedVy;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}