//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjInstallation_Type_AR.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjInstallation_Type_AR::CObjInstallation_Type_AR(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_IT_ARx = x;
	m_IT_ARy = y;

}

//イニシャライズ
void CObjInstallation_Type_AR::Init()
{
	//初期化
	m_IT_ARvx = 0.0f; //位置更新
	m_IT_ARvy = 0.0f;

	//描画サイズ
	m_dst_size = 50.0f;

	//HitBoxサイズ
	m_HitSize_x = 100;
	m_HitSize_y = 60;

	//補充フラグ
	m_Replenishment_flg = false;
	//再補充タイム
	m_Replenishment_time = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_IT_ARx, m_IT_ARy, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_AR, 6);

}

//アクション
void CObjInstallation_Type_AR::Action()
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
	hit_gen->SetPos(m_IT_ARx, m_IT_ARy); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			//主人公に当たると弾補充
			if (((UserData*)Save::GetData())->choose == 0)
			{
				((UserData*)Save::GetData())->AR_load += 200; //アサルトライフル		
				aitemfont->SetAitemNum(200); //弾数表示
			}
			else if (((UserData*)Save::GetData())->choose == 1)
			{
				((UserData*)Save::GetData())->AR_load += 100; //アサルトライフル		
				aitemfont->SetAitemNum(100); //弾数表示
			}
			else if (((UserData*)Save::GetData())->choose == 2)
			{
				((UserData*)Save::GetData())->AR_load += 60; //アサルトライフル		
				aitemfont->SetAitemNum(60); //弾数表示
			}
			aitemfont->SetAGF(2);
			Audio::Start(12); //効果音再生
			//補充フラグ
			m_Replenishment_flg = true;
			//再補充タイム
			m_Replenishment_time = 1800;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	//主人公の移動に合わせる
	m_IT_ARx -= hvx;
	m_IT_ARy -= hvy;

	//再補充タイム
	if (m_Replenishment_time > 0)
	{
		m_Replenishment_time--;
	}
}

//ドロー
void CObjInstallation_Type_AR::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 205.0f;
	src.m_left = 594.0f;
	src.m_right = 660.0f;
	src.m_bottom = 250.0f;

	//描画処理
	dst.m_top = 0.0f + m_IT_ARy;
	dst.m_left = 0.0f + m_IT_ARx;
	dst.m_right = m_dst_size * 2 + m_IT_ARx;
	dst.m_bottom = m_dst_size + m_IT_ARy;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}