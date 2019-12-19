//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjMeme_Neutralization_Device.h"

//使用するネームスペース
using namespace GameL;

//死亡処理
bool m_Meme_death_flg = false; //死亡フラグ

//メニューONOFFフラグ
extern bool Menu_flg;

//イベント成功フラグ
extern bool m_EveSuccess_flg;

//コンストラクタ
CObjMeme_Neutralization_Device::CObjMeme_Neutralization_Device(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Meme_Neu_Devx = x;
	m_Meme_Neu_Devy = y;

}

//イニシャライズ
void CObjMeme_Neutralization_Device::Init()
{
	//初期化
	//描画サイズ
	m_dst_size = 50.0f;
	//HitBoxサイズ
	Hitbox_size = 50;

	//フォント表示タイム
	m_Font_time = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Meme_Neu_Devx, m_Meme_Neu_Devy, Hitbox_size, Hitbox_size, ELEMENT_FIELD, OBJ_MEME_NEUTRALIZATION_DEVICE, 7);

}

//アクション
void CObjMeme_Neutralization_Device::Action()
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
	bool MND = time->GetMNDFlg();

	//イベント情報取得 
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); //対応数　5
	int Eve_Ins = Event->GetEveIns();

	//HitBoxの内容を更新 
	CHitBox* hit_end = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_end->SetPos(m_Meme_Neu_Devx, m_Meme_Neu_Devy); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_end->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (TStop_flg == true)
		{
			m_Font_time = 90; //フォント表示タイム設定
			if (Input::GetVKey(VK_RETURN) == true)
			{
				//ミーム実態イベントor故障イベント時クリア判定
				if (MND == true || (App_Rand > 80 && App_Rand <= 100))
				{
					TStart_flg = true;
					m_Meme_death_flg = true;
					m_EveSuccess_flg = true;
					MND = false;
					time->SetTStart(TStart_flg);					
					Audio::Start(19);
				}
			}
		}		
	}
	else
	{
		m_Meme_death_flg = false;
	}

	//主人公の移動に合わせる
	m_Meme_Neu_Devx -= hvx;
	m_Meme_Neu_Devy -= hvy;

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
void CObjMeme_Neutralization_Device::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END = time->GetENDFlg();

	//イベント情報取得 
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); 

	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒

	//主人公に当たるとフォント表示
	if (m_Font_time > 0)
	{
		Font::StrDraw(L"エンターキーで起動", m_Meme_Neu_Devx -20, m_Meme_Neu_Devy - 30, 15, blk);
	}

	RECT_F src;
	RECT_F dst;
	RECT_F src_cpu;
	RECT_F dst_cpu;

	//切り取り処理
	src.m_top = 50.0f;
	src.m_left = 55.0f;
	src.m_right = 95.0f;
	src.m_bottom = 100.0f;
	//切り取り処理
	src_cpu.m_top = 50.0f;
	src_cpu.m_left = 100.0f;
	src_cpu.m_right = 140.0f;
	src_cpu.m_bottom = 90.0f;
	//描画処理
	dst.m_top = 0.0f + m_Meme_Neu_Devy;
	dst.m_left = 0.0f + m_Meme_Neu_Devx;
	dst.m_right = m_dst_size + m_Meme_Neu_Devx;
	dst.m_bottom = m_dst_size + m_Meme_Neu_Devy;
	//描画処理
	dst_cpu.m_top = 0.0f + m_Meme_Neu_Devy - 20;
	dst_cpu.m_left = 0.0f + m_Meme_Neu_Devx - 10;
	dst_cpu.m_right = (m_dst_size + 10) + m_Meme_Neu_Devx - 10;
	dst_cpu.m_bottom = (m_dst_size + 10) + m_Meme_Neu_Devy - 20;
	if (END == true || (App_Rand > 80 && App_Rand <= 100))
	{		
		Draw::Draw(7, &src_cpu, &dst_cpu, c, 0.0f);
		Draw::Draw(7, &src, &dst, c, 0.0f);
	}
	else if (END == false)
	{		
		Draw::Draw(7, &src_cpu, &dst_cpu, cD, 0.0f);
		Draw::Draw(7, &src, &dst, cD, 0.0f);
	}


}