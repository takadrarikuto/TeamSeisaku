//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"


#include "GameHead.h"
#include "ObjGenerator2.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGenerator2::CObjGenerator2(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Gen2x = x;
	m_Gen2y = y;

}

//イニシャライズ
void CObjGenerator2::Init()
{
	//初期化
	m_Gen2vx = 0.0f; //位置更新
	m_Gen2vy = 0.0f;

	//フォント表示タイム
	m_Font_time = 0;

	//描画サイズ
	m_dst_size = 100.0f;

	//HitBoxサイズ
	m_HitSize_x = 100; 
	m_HitSize_y = 40;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Gen2x, m_Gen2y, m_HitSize_x, m_HitSize_y, ELEMENT_FIELD, OBJ_GENERATOR2, 6);

}

//アクション
void CObjGenerator2::Action()
{

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
	bool Rep_flg = time->GetRepFlg();

	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); //対応数　2

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBoxの内容を更新 
	CHitBox* hit_gen = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_gen->SetPos(m_Gen2x, m_Gen2y); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		
		if (TStop_flg == true)
		{
			m_Font_time = 90; //フォント表示タイム設定
			if (Input::GetVKey(VK_RETURN) == true)
			{
				if (GEN == true)
				{
					TStart_flg = true;
					time->SetTStart(TStart_flg);
					Audio::Start(19);
				}
				if (App_Rand == 2)
				{
					TStart_flg = true;
					time->SetTStart(TStart_flg);
					aitemfont->SetToolBox(true); //画像表示
				}
			}
		}				
	}

	//主人公の移動に合わせる
	m_Gen2x -= hvx;
	m_Gen2y -= hvy;

	//フォント表示時間減少
	if (m_Font_time > 0)
	{
		m_Font_time--;
	}
}

//ドロー
void CObjGenerator2::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool GEN = time->GetGenFlg();
	
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒

	//主人公に当たるとフォント表示
	if (m_Font_time > 0)
	{
		Font::StrDraw(L"エンターキーで起動", m_Gen2x - 20, m_Gen2y - 20, 15, blk);
	}

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//描画処理
	dst.m_top = 0.0f + m_Gen2y;
	dst.m_left = 0.0f + m_Gen2x;
	dst.m_right = m_dst_size + m_Gen2x;
	dst.m_bottom = m_dst_size + m_Gen2y;
	if (GEN == true)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (GEN == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}