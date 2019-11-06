//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjShotGunItem.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjShotGunItem::CObjShotGunItem(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_SG_Item_x = 200;
	m_SG_Item_y = 100;
}

//イニシャライズ
void CObjShotGunItem::Init()
{
	//初期化
	//描画サイズ
	//m_dst_size = 50.0f;
	//XY当たり判定サイズ
	m_XHitbox_size = 38;
	m_YHitbox_size = 30;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_SG_Item_x, m_SG_Item_y, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_SHOTGUN_ITEM, 7);

}

//アクション
void CObjShotGunItem::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//主人公の移動に合わせる
	m_SG_Item_x -= hvx;
	m_SG_Item_y -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_SG_Item_x + 1, m_SG_Item_y + 1); //当たり判定の位置更新

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hero->SetSG(80);		//主人公に当たると弾補充
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //所有するHitBoxを削除する
	}

}

//ドロー
void CObjShotGunItem::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 4.0f;
	src.m_left = 152.0f;
	src.m_right = 170.0f;
	src.m_bottom = 18.0f;

	//描画処理
	dst.m_top = 0.0f + m_SG_Item_y;
	dst.m_left = 0.0f + m_SG_Item_x;
	dst.m_right = 38.0f + m_SG_Item_x;
	dst.m_bottom = 30.0f + m_SG_Item_y;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}