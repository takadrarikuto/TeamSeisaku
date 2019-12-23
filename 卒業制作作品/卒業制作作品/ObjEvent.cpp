//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjEvent.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//イベント失敗フラグ
bool m_EveMiss_flg = false;

//イベント成功フラグ
bool m_EveSuccess_flg = false;

//イニシャライズ
void CObjEvent::Init()
{
	//初期化
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();

	//イベント時間
	m_Event_time = 0; 
	//装置故障イベント時の装置ランダム選択
	m_App_Rand_Flg = 0;
	//イベントフラグ
	m_Event_time_flg = false;
	//イベントタイムペナルティ
	m_Event_TimePenalty = false;
	//イベントペナルティ(球体型敵)フラグ
	m_EventPenalty_Enemy_flg = false;
	//イベントペナルティ(ミーム実態)フラグ
	m_EventPenalty_Meme_flg = false;
	//イベント指示表示タイム
	m_Event_Instruction_time = 0;  

}

//アクション
void CObjEvent::Action()
{
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float h_x = hero->GetX();
	float h_y = hero->GetY();
	float h_vx = hero->GetVX();
	float h_vy = hero->GetVY();
	int h_hp = hero->GetHP();
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop(); 
	bool TStart_flg = time->GetTStart();
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();
	bool MND_flg = time->GetMNDFlg();
	bool Rep_flg = time->GetRepFlg();

	//ツールボックス情報取得
	CObjToolBox* Tool = (CObjToolBox*)Objs::GetObj(OBJ_TOOLBOX);
	float Tool_box_X;
	float Tool_box_Y;
	if (Tool != nullptr)
	{
		Tool_box_X = Tool->GetToolX();
		Tool_box_Y = Tool->GetToolY();
	}

	//アイテムフォント情報取得
	CObjAitemFont* Aitem_Font = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);
	bool Tool_Box_flg;
	if (Aitem_Font != nullptr)
	{
		Tool_Box_flg = Aitem_Font->GetTool_Box();
	}

	//壁4(下)情報取得
	CObjWall4* Wall4 = (CObjWall4*)Objs::GetObj(OBJ_WALL);
	float Wall_X = Wall4->GetX() - h_vx;
	float Wall_Y = Wall4->GetY() - h_vy;	

	//タイムが止まるとイベントタイムスタート
	if (Menu_flg == false && TStop_flg == true)
	{		
		//イベント別タイム設定		
		if (m_Event_time_flg == false)
		{
			//発電機イベント
			if (Gen_flg == true)
			{
				m_Event_time = 50; //1850 ＝ 30秒
			}
			//敵無力化装置イベント
			if (END_flg == true)
			{
				m_Event_time = 3650; //3650 ＝ 60秒
			}
			//ミーム実態無力化装置イベント
			if (MND_flg == true)
			{
				m_Event_time = 3650; //3650 ＝ 60秒
			}
			//装置修理イベント
			if (Rep_flg == true)
			{
				m_Event_time = 5450; //5450 ＝ 90秒
				m_App_Rand_Flg = rand() % 101; //装置故障イベント時の装置ランダム選択
				m_App_Rand_Flg = 10;
				if (m_App_Rand_Flg == 0)
				{
					m_App_Rand_Flg = 1; //装置故障イベント時の装置ランダム選択が0のままになった時1にする
				}
				//1^20 = 発電機,21^40 = 発電機2,41^60 = 敵無力化装置,61^80 = 敵無力化装置2,81^100 = 対ミーム実態敵無力化装置
				//工具箱オブジェクト作成
				CObjToolBox* Toolbox = new CObjToolBox(Wall_X + 1220, Wall_Y - 150);
				Objs::InsertObj(Toolbox, OBJ_TOOLBOX, 4);
			}
			m_Event_time_flg = true;			
			m_Event_Instruction_time = EVENT_INSTRUCTION; //イベント指示表示タイム : 3秒増加
			m_EveMiss_flg = false;
			Audio::Start(16);
		}					
		else if (TStop_flg == false)
		{
			m_Event_time_flg = false;
		}
		if (m_Event_Instruction_time > 0)
		{
			//イベント指示表示タイム減少
			m_Event_Instruction_time--;
		}
		else if (m_Event_Instruction_time == 0)
		{
			if (m_Event_time > 0)
			{
				//イベントタイム減少
				m_Event_time--;
			}
		}
	}	
	if(TStop_flg == false)
	{
	//初期化				
		m_Event_Instruction_time = 0; //イベント指示表示タイム
		m_Event_time_flg = false; //イベントタイムフラグ
		m_Event_TimePenalty = false; //発電機イベントペナルティ
	//修理イベントペナルティ
		m_EventPenalty_Enemy_flg = false; //イベントペナルティ(球体型敵)フラグ
		m_EventPenalty_Meme_flg = false; //イベントペナルティ(ミーム実態)フラグ	
	}
	//イベントタイムが0になる時初期化
	if (m_Event_time <= 0)
	{
		if (TStop_flg == true)
		{
			//初期化
			//イベントタイム関係
			m_Event_time_flg = false;
			TStop_flg = false;
			TStart_flg = true;			
			time->SetTStart(TStart_flg);
			m_EveMiss_flg = true;
		}

		//イベントタイムペナルティ
		//発電機イベント
		if (Gen_flg == true)
		{
			m_Event_TimePenalty = true;
		}
		//修理イベント
		if (Rep_flg == true)
		{
			//対象が発電気の時			
			if ((m_App_Rand_Flg > 0 && m_App_Rand_Flg <= 20) || (m_App_Rand_Flg > 20 && m_App_Rand_Flg <= 40))
			{
				m_Event_TimePenalty = true;
			}
			//対象が無力化装置の時
			if ((m_App_Rand_Flg > 40 && m_App_Rand_Flg <= 60) || (m_App_Rand_Flg > 60 && m_App_Rand_Flg <= 80))
			{
				m_EventPenalty_Enemy_flg = true;//イベントペナルティ(球体型敵)フラグ				
			}
			//対象が対ミーム実態無力化装置の時
			if (m_App_Rand_Flg > 80 && m_App_Rand_Flg <= 100)
			{			
				m_EventPenalty_Meme_flg = true; //イベントペナルティ(ミーム実態)フラグ
			}
			m_App_Rand_Flg = 0;
		}
	}

	//主人公のHPが0になると表示停止
	if (h_hp <= 0)
	{
		m_EveMiss_flg = false;
		m_EveSuccess_flg = false;
	}
}

//ドロー
void CObjEvent::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();
	bool MND_flg = time->GetMNDFlg();
	bool Rep_flg = time->GetRepFlg();

	//m_timeから秒分を求める
	int minute;//分
	int second;//秒

	second = (m_Event_time / 60) % 60;	//秒
	minute = (m_Event_time / 60) / 60;	//分

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒
	wchar_t str[128];
	wchar_t str_a[128];
	wchar_t event[128];
	wchar_t event_a[128];

	//表示切替
	//イベントタイム
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

	//イベント内容
		//発電機イベント
		if (Gen_flg == true)
		{
			swprintf_s(event, L"イベント発生中 : 発電機が停止しました。"); //イベント内容
			swprintf_s(event_a, L"クリア条件 : 発電機を再起動しろ。"); //クリア条件
		}
		//敵無力化装置イベント
		if (END_flg == true)
		{
			swprintf_s(event, L"イベント発生中 : SCP-354-3が大量発生しました。"); //イベント内容
			swprintf_s(event_a, L"クリア条件 : 無力化装置を起動し、SCP-354-3を排除しろ。"); //クリア条件
		}
		//ミーム実態無力化装置イベント
		if (MND_flg == true)
		{
			swprintf_s(event, L"イベント発生中 : SCP-354-13が出現しました。"); //イベント内容
			swprintf_s(event_a, L"クリア条件 : 対ミーム実態無力化装置を起動し、SCP-354-13を排除しろ。"); //クリア条件
		}
		//装置修理イベント
		if (Rep_flg == true)
		{
			swprintf_s(event, L"イベント発生中 : 装置が故障しました。"); //イベント内容
			swprintf_s(event_a, L"クリア条件 : ツールボックスを回収し、故障した装置を直せ。"); //クリア条件
		}
		Font::StrDraw(event, 7, 127, 20, c);
		Font::StrDraw(event_a, 7, 153, 20, c);
	}
		
}