//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjGenerator.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGenerator::CObjGenerator(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Genx = x;
	m_Geny = y;
	
}

//イニシャライズ
void CObjGenerator::Init()
{
	//初期化
	m_Genvx = 0.0f; //位置更新
	m_Genvy = 0.0f;

	//描画サイズ
	m_dst_size = 100.0f; 

	//HitBoxサイズ
	m_HitSize_x = 100; 
	m_HitSize_y = 40;

	//タイム減少フラグ
	m_Time_CutBack_flg = false;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Genx, m_Geny, m_HitSize_x, m_HitSize_y, ELEMENT_FIELD, OBJ_GENERATOR, 6);

}

//アクション
void CObjGenerator::Action()
{
	m_Time_CutBack_flg = false;

	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();
	
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	bool GEN = time->GetGenFlg();

	//HitBoxの内容を更新 
	CHitBox* hit_gen = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_gen->SetPos(m_Genx, m_Geny); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && TStop_flg == true
			&& GEN == true)
		{
			TStart_flg = true;
			m_Time_CutBack_flg = true;
			time->SetTStart(TStart_flg);
		}
	}

	//主人公の移動に合わせる
	m_Genx -= hvx;
	m_Geny -= hvy;

}

//ドロー
void CObjGenerator::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool GEN = time->GetGenFlg();

	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//描画処理
	dst.m_top = 0.0f + m_Geny;
	dst.m_left = 0.0f + m_Genx;
	dst.m_right = m_dst_size + m_Genx;
	dst.m_bottom = m_dst_size + m_Geny;
	if (GEN == true)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (GEN == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}