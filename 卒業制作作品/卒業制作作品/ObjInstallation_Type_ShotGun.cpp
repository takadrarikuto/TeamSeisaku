//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjInstallation_Type_ShotGun.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjInstallation_Type_ShotGun::CObjInstallation_Type_ShotGun(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_IT_SHGx = x;
	m_IT_SHGy = y;

}

//イニシャライズ
void CObjInstallation_Type_ShotGun::Init()
{
	//初期化
	m_IT_SHGvx = 0.0f; //位置更新
	m_IT_SHGvy = 0.0f;

	//描画サイズ
	m_dst_size = 50.0f;

	//HitBoxサイズ
	m_HitSize_x = 100;
	m_HitSize_y = 60;

	//補充フラグ
	m_Replenishment_flg = false; 
	//再補充タイム
	m_Replenishment_time = 0; 

	//再補充完了フォント表示フラグ
	m_Replenishment_Font_flg = false;
	//再補充完了フォント表示タイム
	m_Replenishment_Font_time = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_IT_SHGx, m_IT_SHGy, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_SHG, 6);

}

//アクション
void CObjInstallation_Type_ShotGun::Action()
{

	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBoxの内容を更新 
	CHitBox* hit_gen = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_gen->SetPos(m_IT_SHGx, m_IT_SHGy); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			((UserData*)Save::GetData())->SHG_load += 20;//ショットガン
			aitemfont->SetAGF(1); 
			aitemfont->SetAitemNum(20);			
			Audio::Start(12); //効果音再生

			//再補充タイム
			m_Replenishment_time = 1800;
			//再補充完了フォント表示タイム
			m_Replenishment_Font_time = REPLENIShHMENT_FONT_TIME;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	//主人公の移動に合わせる
	m_IT_SHGx -= hvx;
	m_IT_SHGy -= hvy;

	//再補充タイム
	if (m_Replenishment_time > 0)
	{
		m_Replenishment_time--;		
	}
	else if (m_Replenishment_time == 0)
	{		
		//再補充完了フォント表示タイム減少処理
		if (m_Replenishment_Font_time > 0)
		{
			m_Replenishment_Font_time--; //再補充完了フォント表示タイム現象										
			m_Replenishment_Font_flg = true; //再補充完了フォント表示

			//効果音再生
			if (m_Replenishment_Font_time == REPLENIShHMENT_FONT_TIME)
			{
				Audio::Start(8); 
			}			
		}
		else if (m_Replenishment_Font_time == 0)
		{
			//再補充完了フォント表示フラグ初期化
			m_Replenishment_Font_flg = false;
		}
	}
	
}

//ドロー
void CObjInstallation_Type_ShotGun::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };

	wchar_t str[256];

	if (m_Replenishment_Font_time > 0 && m_Replenishment_Font_flg == true)
	{
		swprintf_s(str, L"ショットガンが再補充されました。");
		Font::StrDraw(str, 0, 570, 30, c); 
	}
	
	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 140.0f;
	src.m_left = 595.0f;
	src.m_right = 665.0f;
	src.m_bottom = 185.0f;

	//描画処理
	dst.m_top = 0.0f + m_IT_SHGy;
	dst.m_left = 0.0f + m_IT_SHGx;
	dst.m_right = m_dst_size * 2 + m_IT_SHGx;
	dst.m_bottom = m_dst_size + m_IT_SHGy;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}