//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL\Audio.h"

#include "ObjStage.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//イニシャライズ
void CObjStage::Init()
{
	//位置情報初期化
	m_y1 = -600.0f;
	m_y2 = 0.0f;

	//移動ベクトル初期化
	m_vy = 5.0f;
}

//アクション
void CObjStage::Action()
{
	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//画像ループ
		//if (m_y1 > 600.0f)
		//{
		//	m_y1 = -590.0f;
		//}
		//else if (m_y2 > 600.0f)
		//{
		//	m_y2 = -590.0f;
		//}

		////位置更新
		//m_y1 += m_vy;
		//m_y2 += m_vy;
	}
}

//ドロー
void CObjStage::Draw()
{

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//hero_hp = hero->GetHP();	//主人公からHPの情報を取得

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	RECT_F dst1;
	RECT_F dst2;

	wchar_t TIME[128];
	wchar_t HP[128];

	//画面上部のメニュー画面

	Draw::Draw(17, &src, &dst, c, 0.0f);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 799.0f;
	src.m_bottom = 601.0f;

	//表示位置の設定
	dst.m_top = 60.0f;
	dst.m_left = 0.0f;
	dst.m_right = 799.0f;
	dst.m_bottom = 601.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//描画処理
	////1枚目
	//dst1.m_top = 0.0f + m_y1;
	//dst1.m_left = 0.0f;
	//dst1.m_right = 800.0f;
	//dst1.m_bottom = 600.0f + m_y1;
	//Draw::Draw(1, &src1, &dst1, c, 0.0f);
	////2枚目
	//dst2.m_top = 0.0f + m_y2;
	//dst2.m_left = 0.0f;
	//dst2.m_right = 800.0f;
	//dst2.m_bottom = 600.0f + m_y2;
	//Draw::Draw(1, &src1, &dst2, c, 0.0f);

	//TIMEを表示
	swprintf_s(TIME, L"TIME", m_stage_time, 15);
	Font::StrDraw(TIME, 15, 4, 23, c);
	/*swprintf_s(TIME, L"○○", m_stage_time, 15);
	Font::StrDraw(TIME, GAME_TIME_POS_X, GAME_TIME_POS_Y, 25, c);*/

	//HPを表示
	swprintf_s(HP, L"HP:100/100", hero_hp, 15);
	Font::StrDraw(HP, GAME_HP_POS_X, GAME_HP_POS_Y, 37, c);

	//武器使用可数を表示
	swprintf_s(HP, L"武器×10", hero_hp, 15);
	Font::StrDraw(HP, 285, 15, 37, c);

	//その他表示
	Font::StrDraw(L"武器切替：左右キー", 470, 13, 18, c);
	Font::StrDraw(L"MENU画面：Rキー", 470, 36, 18, c);
	Font::StrDraw(L"リロード：Eキー", 640, 13, 18, c);
	Font::StrDraw(L"グレネード：Qキー", 640, 36, 18, c);
	/*if (hero_hp < 10)
	{
		swprintf_s(HP, L"/", hero_hp, 15);
		Font::StrDraw(HP, 129, GAME_HP_POS_Y, 37, c);
		swprintf_s(HP, L"%d", 20 + g_hero_max_hp, 15);
		Font::StrDraw(HP, 144, 10, 27, c);
	}
	else
	{
		swprintf_s(HP, L"/", hero_hp, 15);
		Font::StrDraw(HP, 148, GAME_HP_POS_Y, 37, c);
		swprintf_s(HP, L"%d", 20 + g_hero_max_hp, 15);
		Font::StrDraw(HP, 163, 10, 27, c);
	}*/
}