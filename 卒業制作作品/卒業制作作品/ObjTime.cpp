//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include <time.h>

#include "GameHead.h"
#include "ObjTime.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;
//タイム減少フラグ
extern bool m_Time_GenEve_CutBack_flg;
extern bool m_Time_Gen2Eve_CutBack_flg;

//イベント用タイムONOFFフラグ
//bool m_Evetime_flg = false;

//イニシャライズ
void CObjTime::Init()
{
	//初期化
	m_time = 10850; //10850 = 3分
	 //イベントランダム変数
	m_Event_Rand_num = 0;
	//イベント開始時間
	m_time_event = 9050;
	
	m_flag_time = true;
	m_Stop_flg = false; //計測停止フラグ
	m_Start_flg = false; //測定開始フラグ

	m_Gen_flg = false; //発電機起動フラグ
	m_END_flg = false; //敵無力化装置フラグ
	m_MND_flg = false; //ミーム実態無力化装置フラグ
}

//アクション
void CObjTime::Action()
{
	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	bool Time_Pena = Event->GetEveTimPena();

	//制限時間カウントダウン
	if (Menu_flg == false && m_Stop_flg == false)
	{
		if (m_time > 0)
		{
			m_time--;
		}
	}
	//イベント開始、計測停止処理
	if (m_time == m_time_event && m_Stop_flg == false)
	{		
		m_Event_Rand_num = rand() % 100;
		////イベントランダム選択処理
		if (m_Event_Rand_num > 0/*< 50*/)
		{
			m_Gen_flg = true;
		}
		/*else if (m_Event_Rand_num>= 50)
		{
			m_END_flg = true;
		}*/
		/*if (m_Event_Rand_num >= 0)
		{
			m_MND_flg = true;
		}*/
		m_Stop_flg = true;
	}
	//タイム再スタート処理
	if (m_Start_flg == true)
	{		
		//イベント開始時間減少
		m_time_event -= 1800; //30秒減少
		//発電機イベント失敗時タイム増加
		if (Time_Pena == true)
		{
			m_time += 1800; //30秒増加
			Time_Pena = false;
			Event->SetEveTimPena(Time_Pena);
		}
		//初期化処理
		//タイムストップorスタート
		m_Stop_flg = false;
		m_Start_flg = false;
		//設置物フラグ
		m_Gen_flg = false;
		m_END_flg = false;	
		m_MND_flg = false;		
	}
	else
	{
		m_time_event -= 0;
	}
	//制限時間0でゲームクリアシーン移行
	if (m_time == 0)
	{
		Scene::SetScene(new CSceneClear());
	}
}

//ドロー
void CObjTime::Draw()
{
	//m_timeから秒分を求める
	int minute;//分
	int second;//秒

	second = (m_time / 60) % 60;	//秒
	minute = (m_time / 60) / 60;	//分

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	wchar_t str[128];

	//分：秒の値を文字列化
	if (second < 10)
		swprintf_s(str, L"%d:0%d", minute, second);//秒の1桁目に0を用意
	else
		swprintf_s(str, L"%d:%d", minute, second);

	Font::StrDraw(str, 10, 30, 28, c);

	if (minute == 1 && second == 0 || minute == 0)
	{
		Font::StrDraw(str, 10, 30, 28, r);
	}
}