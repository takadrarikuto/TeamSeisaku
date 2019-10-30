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
	m_Healx = 100;
	m_Healy = 100;

}

//イニシャライズ
void CObjHeal::Init()
{
	//初期化
	//描画サイズ
	m_dst_size = 50.0f;
	//XY当たり判定サイズ
	m_XHitbox_size = 29;
	m_YHitbox_size = 27;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Healx, m_Healy, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_HEAL, 7);

}

//アクション
void CObjHeal::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//主人公の移動に合わせる
	m_Healx -= hvx;
	m_Healy -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_Healx + 55, m_Healy + 55); //当たり判定の位置更新

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hero->SetHP(100);
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //回復箱が所有するHitBoxを削除する
	}

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
	dst.m_top = 85.0f + m_Healy;
	dst.m_left = 85.0f + m_Healx;
	dst.m_right = m_dst_size + m_Healx;
	dst.m_bottom = m_dst_size + m_Healy;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}