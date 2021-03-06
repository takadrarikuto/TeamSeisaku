//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjSniperRifleItem.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSniperRifleItem::CObjSniperRifleItem(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_SR_Item_x = x;
	m_SR_Item_y = y;
}

//イニシャライズ
void CObjSniperRifleItem::Init()
{
	//初期化
	//XY当たり判定サイズ
	m_XHitbox_size = 34;
	m_YHitbox_size = 22;

	//スナイパーライフル弾数回復量
	m_SR_num_max = 0; 

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_SR_Item_x, m_SR_Item_y, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_SNIPERRIFLE_ITEM, 7);
	
}

//アクション
void CObjSniperRifleItem::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//主人公の移動に合わせる
	m_SR_Item_x -= hvx;
	m_SR_Item_y -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_SR_Item_x + 1, m_SR_Item_y + 1); //当たり判定の位置更新

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//主人公に当たると弾補充
		if (((UserData*)Save::GetData())->choose == 0)
		{
			m_SR_num_max = 15; //スナイパーライフル弾数回復量変更
			((UserData*)Save::GetData())->SR_load += m_SR_num_max; //スナイパーライフル弾数回復
			aitemfont->SetAitemNum(m_SR_num_max); //スナイパーライフル数表示
		}
		else if (((UserData*)Save::GetData())->choose == 1)
		{
			m_SR_num_max = 10; //スナイパーライフル弾数回復量変更
			((UserData*)Save::GetData())->SR_load += m_SR_num_max; //スナイパーライフル弾数回復
			aitemfont->SetAitemNum(m_SR_num_max); //スナイパーライフル数表示
		}
		else if (((UserData*)Save::GetData())->choose == 2)
		{
			m_SR_num_max = 5; //スナイパーライフル弾数回復量変更
			((UserData*)Save::GetData())->SR_load += m_SR_num_max; //スナイパーライフル弾数回復
			aitemfont->SetAitemNum(m_SR_num_max); //スナイパーライフル数表示
		}			
		aitemfont->SetAGF(3); //フォント表示
		Audio::Start(12); //効果音再生
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //所有するHitBoxを削除する
	}
}

//ドロー
void CObjSniperRifleItem::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 9.0f;
	src.m_left = 218.0f;
	src.m_right = 234.0f;
	src.m_bottom = 19.0f;

	//描画処理
	dst.m_top = 0.0f + m_SR_Item_y;
	dst.m_left = 0.0f + m_SR_Item_x;
	dst.m_right = 34.0f + m_SR_Item_x;
	dst.m_bottom = 22.0f + m_SR_Item_y;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}