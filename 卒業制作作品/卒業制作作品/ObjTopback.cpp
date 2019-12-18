//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "ObjTopback.h"

//使用するネームスペース
using namespace GameL;

//計測停止フラグ
//extern bool m_Stop_flg;

//イベント用タイムONOFFフラグ
//extern bool m_Evetime_flg;

//メニューONOFFフラグ
extern bool Menu_flg;

//タイムストップフラグ
extern bool TStop_flg;

//イベントフラグ
extern bool Gen_flg;
extern bool END_flg;
extern bool MND_flg;
extern bool Rep_flg;

//イベント失敗フラグ
extern bool m_EveMiss_flg;

//イベント成功フラグ
extern bool m_EveSuccess_flg;

//イニシャライズ
void CObjTopback::Init()
{
	evemiss_time = 0;
	evesuc_time = 0;
}

//アクション
void CObjTopback::Action()
{
	
}

//ドロー
void CObjTopback::Draw()
{
	//主人公から各残り弾数情報を取得(装備分)
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int h_hp = hero->GetHP();
	
	hg_pb_e = hero->GetHG_E();	//ハンドガン
	sg_pb_e = hero->GetSG_E();	//ショットガン
	ar_pb_e = hero->GetAR_E();	//アサルトライフル
	sr_pb_e = hero->GetSR_E();	//スナイパーライフル
	rl_pb_e = hero->GetRL_E();	//ロケットランチャー
	rg_pb_e = hero->GetRG_E();	//レールガン
	ws_num = hero->GetWS();

	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();

	//イベント
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_time;
	bool EveMiss_flg;
	if (Event != nullptr)
	{
		Eve_time = Event->GetEveIns();
		EveMiss_flg = Event->GetEveMiss();
	}
	//bool EveSuccess_flg = eve->GetEveSuc();

	//設置型アイテムオブジェクト
	CObjInstallation_Type_ShotGun* IT_SHG = (CObjInstallation_Type_ShotGun*)Objs::GetObj(OBJ_INSTALL_TYPE_SHG);
	bool SHG_Rep_Font_flg = IT_SHG->GetRepFontflg();
	CObjInstallation_Type_AR* IT_AR = (CObjInstallation_Type_AR*)Objs::GetObj(OBJ_INSTALL_TYPE_AR);
	bool AR_Rep_Font_flg = IT_AR->GetRepFontflg();
	CObjInstallation_Type_SR* IT_SR = (CObjInstallation_Type_SR*)Objs::GetObj(OBJ_INSTALL_TYPE_SR);
	bool SR_Rep_Font_flg = IT_SR->GetRepFontflg();
	CObjInstallation_Type_RandBox* IT_RAND = (CObjInstallation_Type_RandBox*)Objs::GetObj(OBJ_INSTALL_TYPE_RANDBOX);
	bool RAND_Rep_Font_flg = IT_RAND->GetRepFontflg();

	//アイテム獲得情報取得
	CObjAitemFont* aitf = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);
	Aitem_get_font = aitf->GetA_G_F();

	//描画カラー情報　R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//黄
	float a[4] = { 1.0f,1.0f,1.0f,0.6f };
	float a2[4] = { 1.0f,1.0f,1.0f,0.8f };
	float a3[4] = { 1.0f,1.0f,1.0f,0.4f };

	RECT_F src;		//描画元切り取り位置
	RECT_F dst;		//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//上部描画
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(30, &src, &dst, a3, 0.0f);

	//上部用背景--------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//上部描画
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 270.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(30, &src, &dst, c, 0.0f);
	
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//上部描画
	dst.m_top = 0.0f;
	dst.m_left = 270.0f;
	dst.m_right = 455.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(31, &src, &dst, c, 0.0f);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//上部描画
	dst.m_top = 0.0f;
	dst.m_left = 455.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(30, &src, &dst, c, 0.0f);
	//------------------------------------------------------------------

	//イベントタイム用背景--------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//描画
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 115.0f;
	dst.m_bottom = 115.0f;

	//タイムストップフラグオンでイベントタイム用背景表示
	if (TStop_flg == true)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	//------------------------------------------------------------------

	//イベント情報背景--------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//描画
	dst.m_top = 120.0f;//63
	dst.m_left = 0.0f;//0
	dst.m_right = 675.0f;//115
	dst.m_bottom = 180.0f;//115

	//タイムストップフラグオンでイベント用背景表示
	if (Menu_flg == false && TStop_flg == true)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}

	//イベント失敗時
	if (Menu_flg == false && EveMiss_flg == true)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;
		//描画
		dst.m_top = 120.0f;//63
		dst.m_left = 0.0f;//0
		dst.m_right = 270.0f;//115
		dst.m_bottom = 180.0f;//115

		//主人公のHPが0になると表示停止
		if (h_hp > 0)
		{
			evemiss_time++;
			if (evemiss_time == 1)
			{
				Audio::Start(17);
			}
			if (evemiss_time < 200)
			{
				Draw::Draw(30, &src, &dst, a, 0.0f);
				Font::StrDraw(L"イベント失敗", 25, 133, 35, r);
			}
			if (evemiss_time > 200)
			{
				EveMiss_flg = false;
			}
		}
		else
		{
			m_EveSuccess_flg = false;
		}
	}

	//イベント成功時
	if (Menu_flg == false && m_EveSuccess_flg == true)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;
		//描画
		dst.m_top = 120.0f;//63
		dst.m_left = 0.0f;//0
		dst.m_right = 270.0f;//115
		dst.m_bottom = 180.0f;//115

		//主人公のHPが0になると表示停止
		if (h_hp > 0)
		{
			evesuc_time++;
			if (evesuc_time < 200)
			{
				Draw::Draw(30, &src, &dst, a, 0.0f);
				Font::StrDraw(L"イベント成功！", 15, 133, 35, y);
			}
			if (evesuc_time > 200)
			{
				m_EveSuccess_flg = false;
			}
		}		
		else
		{
			m_EveSuccess_flg = false;
		}
	}
	if (m_EveSuccess_flg == false)
	{
		evesuc_time = 0;
	}

	//------------------------------------------------------------------

	//リロード文字用背景------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//描画
	dst.m_top = 63.0f;
	dst.m_left = 270.0f;
	dst.m_right = 455.0f;
	dst.m_bottom = 113.0f;

	if (hg_pb_e == 0 && ws_num == 0)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (sg_pb_e == 0 && ws_num == 1)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (ar_pb_e == 0 && ws_num == 2)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (sr_pb_e == 0 && ws_num == 3)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (rl_pb_e == 0 && ws_num == 4)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (rg_pb_e == 0 && ws_num == 5)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	//------------------------------------------------------------------

	//アイテムゲット時用背景------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//描画
	dst.m_top = 565.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	if (Aitem_get_font > 0)
	{
		if (Aitem_get_font == 1)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 2)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 3)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 4)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 5)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 6)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 7)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 8)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 9)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
	}
	//設置型アイテム補充時用背景------------------------------------------------
	if (Menu_flg == false)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;
		//描画
		dst.m_top = 565.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		if (SHG_Rep_Font_flg == true || AR_Rep_Font_flg == true || SR_Rep_Font_flg == true || RAND_Rep_Font_flg == true)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
	}
	
	//------------------------------------------------------------------
}