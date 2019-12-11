//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
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

//イニシャライズ
void CObjTopback::Init()
{

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

	//設置型アイテムオブジェクト
	CObjInstallation_Type_ShotGun* IT_SHG = (CObjInstallation_Type_ShotGun*)Objs::GetObj(OBJ_INSTALL_TYPE_SHG);
	int SHG_Rep_Font = IT_SHG->GetRepFontTime();

	//アイテム獲得情報取得
	CObjAitemFont* aitf = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);
	Aitem_get_font = aitf->GetA_G_F();

	//描画カラー情報　R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.6f };
	float a2[4] = { 1.0f,1.0f,1.0f,0.8f };

	RECT_F src;		//描画元切り取り位置
	RECT_F dst;		//描画先表示位置

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

	//タイムストップフラグオンでイベントタイム用背景表示
	if (Menu_flg == false && TStop_flg == true)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
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
	if (SHG_Rep_Font == true)
	{
		Draw::Draw(30, &src, &dst, a2, 0.0f);
	}

	//------------------------------------------------------------------
}