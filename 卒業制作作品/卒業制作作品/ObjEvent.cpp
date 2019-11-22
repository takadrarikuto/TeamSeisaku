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
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();

	//イベント時間
	m_Event_time = 1200; 
	//イベントフラグ
	m_Event_time_flg = false;

}

//アクション
void CObjEvent::Action()
{
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int h_hp = hero->GetHP();
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();
	
	//タイムが止まるとイベントタイムスタート
	if (Menu_flg == false && TStop_flg == true)
	{		
		//イベント別タイム設定
		//発電機イベント
		if (m_Event_time_flg == false)
		{
			if (Gen_flg == true)
			{
				m_Event_time = 1850; //1850 ＝ 30秒
			}
			//敵無力化装置イベント
			else if (END_flg == true)
			{
				m_Event_time = 3600; //3600 ＝ 60秒
			}
			m_Event_time_flg = true;
		}	
		m_Event_time--;
	}	
	else if(Menu_flg == false && TStop_flg == false)
	{
		m_Event_time_flg = false;
	}
	//イベントタイムが0になるor主人公の体力が0になる時初期化
	if (m_Event_time == 0 || h_hp <= 0)
	{
		//イベントタイム
		m_Event_time_flg = false;
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