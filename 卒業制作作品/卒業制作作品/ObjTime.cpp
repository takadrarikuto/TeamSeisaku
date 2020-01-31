//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include"GameL\UserData.h"

#include <time.h>

#include "GameHead.h"
#include "ObjTime.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTime::Init()
{
	//初期化
	m_time = ((UserData*)Save::GetData())->Level_Time;
	
	//時間停止
	m_time_stop = 0; 
	 //イベントランダム変数
	m_Event_Rand_num = 0;
	//イベント開始時間
	m_time_event = ((UserData*)Save::GetData())->Event_Time;

	m_Stop_flg = false; //計測停止フラグ
	m_Start_flg = false; //測定開始フラグ

	m_Gen_flg = false; //発電機起動フラグ
	m_END_flg = false; //敵無力化装置フラグ
	m_MND_flg = false; //ミーム実態無力化装置フラグ
	m_Repairing_flg = false; //装置修理イベントフラグ

}

//アクション
void CObjTime::Action()
{
	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	bool Time_Pena = Event->GetEveTimPena();
	int Eve_Ins = Event->GetEveIns();

	//敵無力化装置情報取得
	CObjEnemy_Neutralization_Device* END_Deat = (CObjEnemy_Neutralization_Device*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
	//敵無力化装置2情報取得
	CObjEnemy_Neutralization_Device2* END2_Deat = (CObjEnemy_Neutralization_Device2*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE2);

	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg;
	if (Menu != nullptr)
	{
		Menu_flg = Menu->GetMenu();
	}

	//制限時間カウントダウン
	if (Menu_flg == false && m_Stop_flg == false)
	{
		//タイム減少
		if (m_time > 0 && m_time_stop == 0)
		{
			m_time--;
		}
		//タイム停止時間減少
		if (m_time_stop > 0)
		{
			m_time_stop--;
		}
	}
	//イベント開始、計測停止処理
	if (m_time == m_time_event && m_time > 50)
	{		
		if (m_Stop_flg == false)
		{
			m_Event_Rand_num = rand() % 100;
			//イベントランダム選択処理
			//発電機イベント
			/*if (m_Event_Rand_num > 0 && m_Event_Rand_num <= 50)
			{
				m_Gen_flg = true;
			}
			//敵無力化イベント
			if (m_Event_Rand_num > 50 && m_Event_Rand_num <= 65)
			{
				m_END_flg = true;
				END_Deat->Set_Deat(false); //敵無力化処理初期化
				END2_Deat->Set_Deat2(false); //敵無力化2処理初期化
			}
			//ミーム実態無力化イベント
			if (m_Event_Rand_num > 65 && m_Event_Rand_num <= 80)
			{
				m_MND_flg = true;
			}
			//修理イベント
			if (m_Event_Rand_num > 80 && m_Event_Rand_num <= 100)
			{
				m_Repairing_flg = true;
			}*/
			//ミーム実態無力化イベント
			if (m_Event_Rand_num > 0 && m_Event_Rand_num <= 100)
			{
				m_MND_flg = true;
			}
			m_Stop_flg = true;
		}		
	}
	//タイム再スタート処理
	if (m_Start_flg == true)
	{		
		//初期化処理
		//タイムストップorスタート
		m_Stop_flg = false;
		m_Start_flg = false;
		//設置物フラグ
		m_Gen_flg = false;
		m_END_flg = false;
		m_MND_flg = false;
		//装置修理フラグ
		m_Repairing_flg = false;

		//イベント開始時間減少
		m_time_event -= 1800; //30秒減少
		if (Time_Pena == true)
		{
			//時間停止
			m_time_stop = 1800;//30秒増加
			Time_Pena = false;
			Event->SetEveTimPena(Time_Pena);
		}
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
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//黄
	wchar_t str[128];

	//分：秒の値を文字列化
	if (second < 10)
		swprintf_s(str, L"%d:0%d", minute, second);//秒の1桁目に0を用意
	else
		swprintf_s(str, L"%d:%d", minute, second);

	Font::StrDraw(str, 10, 30, 28, c);	

	if (minute == 1 && second == 0 || minute == 0)
	{
		Font::StrDraw(str, 10, 30, 28, y);
	}

	if (m_time_stop > 0)
	{
		Font::StrDraw(str, 10, 30, 28, r);
	}
}