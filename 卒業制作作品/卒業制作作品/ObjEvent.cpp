//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjEvent.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//イニシャライズ
void CObjEvent::Init()
{
	//初期化
	//イベント時間
	m_Event_time = 1850; //1850 ＝ 30秒

	//m_Stop_flg = false;
	//測定スタートフラグ
	//m_Start_flg = false;
}

//アクション
void CObjEvent::Action()
{
	////発電機情報取得
	//CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	//bool ST_flg = time->GetTS();
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int h_hp = hero->GetHP();
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();

	if (Menu_flg == false && TStop_flg == true)
	{
		m_Event_time--;
	}
	else if(Menu_flg == false && TStop_flg == false)
	{
		m_Event_time = 1850;
	}
	if (m_Event_time == 0 || h_hp <= 0)
	{
		TStart_flg = true;
		time->SetTStart(TStart_flg);		
	}

}

//ドロー
void CObjEvent::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	//m_timeから秒分を求める
	int minute;//分
	int second;//秒

	second = (m_Event_time / 60) % 60;	//秒
	minute = (m_Event_time / 60) / 60;	//分

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	wchar_t str[128];

	//表示切替
	if (TStop_flg == true)
	{
		//イベントTIMEを表示
		Font::StrDraw(L"EVENT TIME", 7, 65, 20, c);

		//分：秒の値を文字列化
		if (second < 10)
			swprintf_s(str, L"%d:0%d", minute, second);//秒の1桁目に0を用意
		else
			swprintf_s(str, L"%d:%d", minute, second);

		Font::StrDraw(str, 27, 85, 28, c);
	}

	/*if (minute == 1 && second == 0 || minute == 0)
	{
		Font::StrDraw(str, 10, 85, 28, r);
	}*/
}