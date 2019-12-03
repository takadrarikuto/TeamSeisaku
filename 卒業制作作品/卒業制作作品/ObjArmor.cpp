//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjArmor.h"

//使用するネームスペース
using namespace GameL;

//HP ONOFFフラグ
extern bool Hp_flg;

//耐久力ONOFFフラグ
extern bool En_flg;

//コンストラクタ
CObjArmor::CObjArmor(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Armorx = x;
	m_Armory = y;

}

//イニシャライズ
void CObjArmor::Init()
{
	//初期化
	//描画サイズ
	m_dst_size = 50.0f;
	//XY当たり判定サイズ
	m_XHitbox_size = 38;
	m_YHitbox_size = 44;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Armorx, m_Armory, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_ARMOR, 7);
	
}

//アクション
void CObjArmor::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//主人公の移動に合わせる
	m_Armorx -= hvx;
	m_Armory -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_Armorx + 1, m_Armory + 1); //当たり判定の位置更新

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hero->SetEN(150);
		aitemfont->SetAGF(8); //フォント表示
		Hp_flg = false;
		En_flg = true;
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //回復箱が所有するHitBoxを削除する
	}

}

//ドロー
void CObjArmor::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理(19*22)
	src.m_top = 9.0f;
	src.m_left = 120.0f;
	src.m_right = 138.0f;
	src.m_bottom = 30.0f;

	//描画処理
	dst.m_top = 0.0f + m_Armory;
	dst.m_left = 0.0f + m_Armorx;
	dst.m_right = 38.0f + m_Armorx;
	dst.m_bottom = 44.0f + m_Armory;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}