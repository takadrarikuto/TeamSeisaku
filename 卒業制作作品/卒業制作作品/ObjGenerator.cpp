//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjGenerator.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//イベント成功フラグ
extern bool m_EveSuccess_flg;

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
	//フォント表示タイム
	m_Font_time = 0;

	//描画サイズ
	m_dst_size = 100.0f; 

	//HitBoxサイズ
	m_HitSize_x = 100; 
	m_HitSize_y = 40;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Genx, m_Geny, m_HitSize_x, m_HitSize_y, ELEMENT_FIELD, OBJ_GENERATOR, 6);

}

//アクション
void CObjGenerator::Action()
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
	int App_Rand = Event->GetApp_Rand(); //対応数　1
	int Eve_Ins = Event->GetEveIns();

	//HitBoxの内容を更新 
	CHitBox* hit_gen = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_gen->SetPos(m_Genx, m_Geny); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{	
		if (TStop_flg == true)
		{
			m_Font_time = 90; //フォント表示タイム設定
			if (Input::GetVKey(VK_RETURN) == true)
			{
				//発電機イベントor修理イベント時クリア判定
				if (GEN == true || App_Rand <= 20)
				{
					TStart_flg = true;
					time->SetTStart(TStart_flg);
					m_EveSuccess_flg = true;
					Audio::Start(19);
				}
			}
		}		
	}

	//主人公の移動に合わせる
	m_Genx -= hvx;
	m_Geny -= hvy;

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false && Eve_Ins == 0)
	{
		//フォント表示時間減少
		if (m_Font_time > 0)
		{
			m_Font_time--;
		}
	}
	
}

//ドロー
void CObjGenerator::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool GEN = time->GetGenFlg();

	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); //対応数　1

	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒

	//主人公に当たるとフォント表示
	if (m_Font_time > 0)
	{
		Font::StrDraw(L"エンターキーで起動", m_Genx - 20, m_Geny - 20, 15, blk);
	}

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
	if (GEN == true || App_Rand == 1)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (GEN == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}