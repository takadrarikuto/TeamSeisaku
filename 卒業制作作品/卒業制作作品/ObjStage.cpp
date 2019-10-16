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

//イニシャライズ
void CObjStage::Init()
{

}

//アクション
void CObjStage::Action()
{

}

//ドロー
void CObjStage::Draw()
{

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//hero_hp = hero->GetHP();	//主人公からHPの情報を取得

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	wchar_t TIME[128];
	wchar_t HP[128];

	//画面上部のメニュー画面

	Draw::Draw(17, &src, &dst, c, 0.0f);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 48.0f;
	dst.m_right = 80.0f;
	dst.m_bottom = 36.0f;
	//Draw::Draw(20, &src, &dst, c, 0.0f);

	//TIMEを表示
	swprintf_s(TIME, L"TIME", m_stage_time, 15);
	Font::StrDraw(TIME, 15, 4, 23, c);
	swprintf_s(TIME, L"○○", m_stage_time, 15);
	Font::StrDraw(TIME, GAME_TIME_POS_X, GAME_TIME_POS_Y, 25, c);

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