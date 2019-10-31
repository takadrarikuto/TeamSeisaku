//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjTime.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

bool m_Stop_flg = false; //計測停止フラグ
bool m_Start_flg = false; //測定開始フラグ

//イベント用タイムONOFFフラグ
//bool m_Evetime_flg = false;

//イニシャライズ
void CObjTime::Init()
{
	//初期化
	m_time = 10850; //10850 = 3分

	m_flag_time = true;
	m_Stop_flg = false; //計測停止フラグ
	m_Start_flg = false; //測定開始フラグ

	m_Gen_flg = false; //発電機起動フラグ
	m_END_flg = false; //敵無力化装置フラグ

	m_Event_num = 0;  //イベント変数

}

//アクション
void CObjTime::Action()
{
	////発電機情報取得
	//CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	//bool ST_flg = time->GetTS();
	////イベント情報取得
	//CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_HEAL);
	//bool Start_flg = Event->GetStartT();

	//制限時間カウントダウン
	if (Menu_flg == false && m_Stop_flg == false)
	{
		if (m_time > 0)
		{
			m_time--;
		}
	}
	//イベント開始、計測停止処理
	if (m_time == 9050 && m_Event_num == 0)
	{
		m_Stop_flg = true;
		m_Event_num = 1;
		//m_Evetime_flg = true;
	}
	else if (m_time == 7250 && m_Event_num == 1)
	{
		m_Stop_flg = true;
		m_Event_num = 2;
		//m_Evetime_flg = true;
	}
	if (m_Start_flg == true)
	{
		m_Stop_flg = false;
		m_Start_flg = false;
	}
	if (m_Event_num == 1)
	{
		m_Gen_flg = true;
	}
	else if (m_Event_num == 2)
	{
		m_END_flg = true;
	}
	////制限時間カウントダウン
	//if (Menu_flg == false && m_Stop_flg == false)
	//{
	//	if (m_time > 0)
	//	{
	//		m_time--;		
	//	}
	//}
	////イベント開始、計測停止処理
	//if (m_time == 9050 && m_Start_num == 0)
	//{
	//	m_Stop_flg = true;
	//	m_Start_num = 1;
	//}
	//if (ST_flg == true)
	//{
	//	m_Stop_flg = false;
	//}
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