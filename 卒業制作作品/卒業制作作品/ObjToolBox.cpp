//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjToolBox.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjToolBox::CObjToolBox(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Healx = x;
	m_Healy = y;

}

//イニシャライズ
void CObjToolBox::Init()
{
	//初期化
	//描画サイズ
	m_dst_size = 50.0f;
	//XY当たり判定サイズ
	m_XHitbox_size = 60;
	m_YHitbox_size = 60;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Healx, m_Healy, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_TOOLBOX, 7);
	
}

//アクション
void CObjToolBox::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);
	
	//主人公の移動に合わせる
	m_Healx -= hvx;
	m_Healy -= hvy;

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_Healx + 1, m_Healy + 1); //当たり判定の位置更新

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		aitemfont->SetAGF(9); //フォント表示
		aitemfont->SetToolBox(true); //画像表示
		Audio::Start(12); //効果音再生
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //工具箱が所有するHitBoxを削除する
	}

}

//ドロー
void CObjToolBox::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 59.0f;
	src.m_left = 4.0f;
	src.m_right = 38.0f;
	src.m_bottom = 93.0f;

	//描画処理
	dst.m_top = 0.0f + m_Healy;
	dst.m_left = 0.0f + m_Healx;
	dst.m_right = 60.0f + m_Healx;
	dst.m_bottom = 60.0f + m_Healy;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}