//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjNet.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjNet::CObjNet(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Netx = x;
	m_Nety = y;
}

//イニシャライズ
void CObjNet::Init()
{
	//初期化
	//位置情報登録(数値=位置調整)
	//m_Netx = 0.0f;
	//m_Nety = 0.0f;

	//描画サイズ
	m_dst_size = 50.0f;	

	//XY当たり判定サイズ
	m_XHitbox_size = 202;
	m_YHitbox_size = 72;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Netx, m_Nety, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_NET, 7);
	////Y軸用
	//if (m_r == 90.0f)
	//{
	//	//XY当たり判定サイズ
	//	m_XHitbox_size = 72;
	//	m_YHitbox_size = 202;
	//	Hits::SetHitBox(this, m_Netx, m_Nety, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_NET, 7);
	//}
	//else if (m_r == 90.0f)
	//{
	//	hit_exp->SetPos(m_Netx + 66, m_Nety - 70); //当たり判定の位置更新
	//}
}

//アクション
void CObjNet::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_Netx + 1, m_Nety + 1); //当たり判定の位置更新
	
	
	

	//主人公の移動に合わせる
	m_Netx -= hvx;
	m_Nety -= hvy;
}

//ドロー
void CObjNet::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 149.0f;
	src.m_left = 248.0f;
	src.m_right = 345.0f;
	src.m_bottom = 246.0f;

	//描画処理(101*36)
	dst.m_top = 0.0f + m_Nety;
	dst.m_left = 0.0f + m_Netx;
	dst.m_right = 202.0f + m_Netx;
	dst.m_bottom = 72.0f + m_Nety;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}