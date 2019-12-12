//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjEnemy_Neutralization_Device2.h"

//使用するネームスペース
using namespace GameL;

//死亡処理
bool m_END2_death_flg = false; //死亡フラグ

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CObjEnemy_Neutralization_Device2::CObjEnemy_Neutralization_Device2(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Enemy_Neu_Dev2x = x;
	m_Enemy_Neu_Dev2y = y;

}

//イニシャライズ
void CObjEnemy_Neutralization_Device2::Init()
{
	//初期化
	m_Enemy_Neu_Dev2_HitSize_x = 55;  //HitBoxサイズ
	m_Enemy_Neu_Dev2_HitSize_y = 50;	

	//フォント表示タイム
	m_Font_time = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Enemy_Neu_Dev2x, m_Enemy_Neu_Dev2y, m_Enemy_Neu_Dev2_HitSize_x, m_Enemy_Neu_Dev2_HitSize_y, ELEMENT_FIELD2, OBJ_ENEMY_NEUTRALIZATION_DEVICE2, 6);

}

//アクション
void CObjEnemy_Neutralization_Device2::Action()
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
	bool END = time->GetENDFlg();
	bool Rep_flg = time->GetRepFlg();

	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); //対応数　4
	int Eve_Ins = Event->GetEveIns();

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBoxの内容を更新 
	CHitBox* hit_end = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_end->SetPos(m_Enemy_Neu_Dev2x, m_Enemy_Neu_Dev2y); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_end->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (TStop_flg == true)
		{
			m_Font_time = 90; //フォント表示タイム設定
			if (Input::GetVKey(VK_RETURN) == true)
			{
				if (END == true)
				{
					TStart_flg = true;
					m_END2_death_flg = true;
					time->SetTStart(TStart_flg);
					Audio::Start(19);
				}
				if (App_Rand == 4)
				{
					TStart_flg = true;
					time->SetTStart(TStart_flg);
					aitemfont->SetToolBox(true); //画像表示
				}
			}
		}		
	}
	else
	{
		m_END2_death_flg = false;
	}

	//主人公の移動に合わせる
	m_Enemy_Neu_Dev2x -= hvx;
	m_Enemy_Neu_Dev2y -= hvy;

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
void CObjEnemy_Neutralization_Device2::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END = time->GetENDFlg();

	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒

	//主人公に当たるとフォント表示
	if (m_Font_time > 0)
	{
		Font::StrDraw(L"エンターキーで起動", m_Enemy_Neu_Dev2x - 20, m_Enemy_Neu_Dev2y - 20, 15, blk);
	}

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 15.0f;
	src.m_left = 110.0f;
	src.m_right = 145.0f;
	src.m_bottom = 80.0f;

	//描画処理
	dst.m_top = 0.0f + m_Enemy_Neu_Dev2y;
	dst.m_left = 0.0f + m_Enemy_Neu_Dev2x;
	dst.m_right = 55.0f + m_Enemy_Neu_Dev2x;
	dst.m_bottom = 105.0f + m_Enemy_Neu_Dev2y;
	if (END == true)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (END == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}


}