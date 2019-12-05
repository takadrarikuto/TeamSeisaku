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

//イニシャライズ
void CObjEvent::Init()
{
	//初期化
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();

	//イベント時間
	m_Event_time = 1850; 
	//装置故障イベント時の装置ランダム選択
	m_App_Rand_Flg = 1;
	//イベントフラグ
	m_Event_time_flg = false;
	//イベントタイムペナルティ
	m_Event_TimePenalty = false;
//距離測定変数
	//発電機
	m_Gene_distance_X = 0; 
	m_Gene_distance_Y = 0; 
	m_Gene_distance_r = 0;
	//発電機2
	m_Gene2_distance_X = 0;
	m_Gene2_distance_Y = 0; 
	m_Gene2_distance_r = 0;
	//敵無力化装置
	m_END_distance_X = 0; 
	m_END_distance_Y = 0; 
	m_END_distance_r = 0;
	//敵無力化装置2
	m_END2_distance_X = 0;
	m_END2_distance_Y = 0; 
	m_END2_distance_r = 0;
	//対ミーム実態無力化装置
	m_MND_distance_X = 0; 
	m_MND_distance_Y = 0; 
	m_MND_distance_r = 0;
	//ツールボックス
	m_Tool_distance_X = 0; 
	m_Tool_distance_Y = 0;
	m_Tool_distance_r = 0;

}

//アクション
void CObjEvent::Action()
{
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float h_x = hero->GetX();
	float h_y = hero->GetY();
	int h_hp = hero->GetHP();
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop(); 
	bool TStart_flg = time->GetTStart();
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();
	bool MND_flg = time->GetMNDFlg();
	bool Rep_flg = time->GetRepFlg();
//装置系
	//発電機情報取得
	CObjGenerator* Gene = (CObjGenerator*)Objs::GetObj(OBJ_GENERATOR);
	float Gene_X = Gene->GetGenX();
	float Gene_Y = Gene->GetGenY();
	CObjGenerator2* Gene2 = (CObjGenerator2*)Objs::GetObj(OBJ_GENERATOR);
	float Gene2_X = Gene2->GetGenX();
	float Gene2_Y = Gene2->GetGenY();
	//敵無力化装置情報取得
	CObjEnemy_Neutralization_Device* END = (CObjEnemy_Neutralization_Device*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
	float END_X = END->GetEndX();
	float END_Y = END->GetEndY();
	CObjEnemy_Neutralization_Device2* END2 = (CObjEnemy_Neutralization_Device2*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
	float END2_X = END2->GetEndX();
	float END2_Y = END2->GetEndY();
	//対ミーム実態無力化装置情報取得
	CObjMeme_Neutralization_Device* MND = (CObjMeme_Neutralization_Device*)Objs::GetObj(OBJ_MEME_NEUTRALIZATION_DEVICE);
	float MND_X = MND->GetMndX();
	float MND_Y = MND->GetMndY();
	//ツールボックス情報取得
	CObjToolBox* Tool = (CObjToolBox*)Objs::GetObj(OBJ_TOOLBOX);
	float Tool_box_X;
	float Tool_box_Y;
	if (Tool != nullptr)
	{
		Tool_box_X = Tool->GetToolX();
		Tool_box_Y = Tool->GetToolY();
	}
	//タイムが止まるとイベントタイムスタート
	if (Menu_flg == false && TStop_flg == true)
	{		
		//イベント別タイム設定		
		if (m_Event_time_flg == false)
		{
			//発電機イベント
			if (Gen_flg == true)
			{
				m_Event_time = 1850; //1850 ＝ 30秒
				Audio::Start(16);
			}
			//敵無力化装置イベント
			else if (END_flg == true)
			{
				m_Event_time = 3600; //3600 ＝ 60秒
				Audio::Start(16);
			}
			//ミーム実態無力化装置イベント
			else if (MND_flg == true)
			{
				m_Event_time = 3600; //3600 ＝ 60秒
				Audio::Start(16);
			}
			//装置修理イベント
			else if (Rep_flg == true)
			{
				m_Event_time = 3600; //3600 ＝ 60秒
				m_App_Rand_Flg = rand() % 5; //装置故障イベント時の装置ランダム選択
				//1 = 発電機,2 = 発電機2,3 = 敵無力化装置,4 = 敵無力化装置2,5 = 対ミーム実態敵無力化装置
				Audio::Start(16);
			}
			m_Event_time_flg = true;
		}	
		if (m_Event_time > 0)
		{
			m_Event_time--;			
		}		
	}	
	else if(Menu_flg == false && TStop_flg == false)
	{
		m_Event_time_flg = false;
		m_Event_TimePenalty = false;
	}
	//イベントタイムが0になるor主人公の体力が0になる時初期化
	if (m_Event_time <= 0 || h_hp <= 0)
	{
		//イベントタイム
		m_Event_time_flg = false;
		TStop_flg = false;
		TStart_flg = true;
		time->SetTStart(TStart_flg);
		//イベントタイムペナルティ
		if (Gen_flg == true)
		{
			m_Event_TimePenalty = true;
			Audio::Start(17);
		}
	}
	
	//主人公から装置までの距離測定
	//	//発電機イベント
	//if (Gen_flg == true)
	//{
	//	m_Gene_distance_X = Gene_X - h_x; //発電機
	//	m_Gene_distance_Y = Gene_Y - h_x;
	//	m_Gene2_distance_X = Gene2_X - h_x; //発電機2
	//	m_Gene2_distance_Y = Gene2_Y - h_x;
	//	//斜めの距離を求める
	//	m_Gene_distance_r = m_Gene_distance_X*m_Gene_distance_X + m_Gene_distance_Y * m_Gene_distance_Y;
	//	m_Gene2_distance_r = m_Gene2_distance_X * m_Gene2_distance_X + m_Gene2_distance_Y * m_Gene2_distance_Y;
	//	sqrt(m_Gene_distance_r);
	//	sqrt(m_Gene2_distance_r);
	//}
	////敵無力化装置イベント
	//else if (END_flg == true)
	//{
	//	m_END_distance_X = END_X - h_x; //敵無力化装置
	//	m_END_distance_Y = END_Y - h_x;
	//	m_END2_distance_X = END2_X - h_x; //敵無力化装置2
	//	m_END2_distance_Y = END2_Y - h_x;
	//}
	////ミーム実態無力化装置イベント
	//else if (MND_flg == true)
	//{
	//	m_MND_distance_X = MND_X - h_x; //対ミーム実態無力化装置
	//	m_MND_distance_Y = MND_Y - h_x;
	//}
	////装置修理イベント
	//else if (Rep_flg == true)
	//{
	//	m_Tool_distance_X = Tool_box_X - h_x; //ツールボックス
	//	m_Tool_distance_Y = Tool_box_Y - h_x;
	//}	
	/*
	r = m_zevx * m_zevx + m_zevy * m_zevy;
	r = sqrt(r); //ルートを求める
	*/
	m_Gene_distance_X = h_x + -Gene_X; //発電機
	m_Gene_distance_Y = h_y + -Gene_Y;
	m_Gene2_distance_X = Gene2_X - h_x; //発電機2
	m_Gene2_distance_Y = Gene2_Y - h_y;
	//斜めの距離を求める
	m_Gene_distance_r = m_Gene_distance_X + m_Gene_distance_Y;
	m_Gene2_distance_r = m_Gene2_distance_X + m_Gene2_distance_Y;
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
	}
	//イベント内容
	//if (Menu_flg == false && TStop_flg == true)
	//{
	//	//発電機イベント
	//	if (Gen_flg == true)
	//	{
	//		swprintf_s(str, L"イベンド発生中 : 発電機が停止しました。"); //イベント内容
	//		swprintf_s(str_a, L"クリア条件 : 発電機を再起動しろ。距離 %dm or %dm",m_Gene_distance_r,m_Gene2_distance_r); //クリア条件
	//	}
	//	//敵無力化装置イベント
	//	else if (END_flg == true)
	//	{
	//		swprintf_s(str, L"イベンド発生中 : SCP-354-3が大量発生しました。"); //イベント内容
	//		swprintf_s(str_a, L"クリア条件 : 無力化装置を起動し、SCP-354-3を排除しろ。"); //クリア条件
	//	}
	//	//ミーム実態無力化装置イベント
	//	else if (MND_flg == true)
	//	{
	//		swprintf_s(str, L"イベンド発生中 : SCP-354-13が出現しました。"); //イベント内容
	//		swprintf_s(str_a, L"クリア条件 : 対ミーム実態無力化装置を起動し、SCP-354-13を排除しろ。"); //クリア条件
	//	}
	//	//装置修理イベント
	//	else if (Rep_flg == true)
	//	{
	//		swprintf_s(str, L"イベンド発生中 : 装置が故障しました。"); //イベント内容
	//		swprintf_s(str_a, L"クリア条件 : ツールボックスを回収し、故障した装置を直せ。"); //クリア条件
	//	}
	//	Font::StrDraw(str, 300, 65, 20, blk);
	//	Font::StrDraw(str_a, 300, 95, 20, blk);
	//}	

	swprintf_s(str, L"イベンド発生中 : 発電機が停止しました。"); //イベント内容
	swprintf_s(str_a, L"クリア条件 : 発電機を再起動しろ。距離 %dｍ or %dｍ",m_Gene_distance_r,m_Gene2_distance_r); //クリア条件
	Font::StrDraw(str, 0, 120, 20, blk);
	Font::StrDraw(str_a, 0, 150, 20, blk);

}