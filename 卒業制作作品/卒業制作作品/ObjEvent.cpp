//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjEvent.h"

//使用するネームスペース
using namespace GameL;

//計測停止フラグ
extern bool m_Stop_flg;

//イニシャライズ
void CObjEvent::Init()
{
	//初期化
	//イベント時間
	m_Evwnt_time = 1800;
	//測定スタートフラグ
	m_Start_flg = false;
}

//アクション
void CObjEvent::Action()
{
	////発電機情報取得
	//CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	//bool ST_flg = time->GetTS();

	/*if (ST_flg == true)
	{
		m_Evwnt_time--;
	}
	if (m_Evwnt_time == 0)
	{
		ST_flg = false;
		m_Start_flg = true;
		m_Evwnt_time = 1800;
	}*/
}

//ドロー
void CObjEvent::Draw()
{
	//m_timeから秒分を求める
	int minute;//分
	int second;//秒

	second = (m_Evwnt_time / 60) % 60;	//秒
	minute = (m_Evwnt_time / 60) / 60;	//分

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	wchar_t str[128];

	/*if (m_Stop_flg == true)
	{*/
		//イベントTIMEを表示
		Font::StrDraw(L"EVENT TIME", 7, 65, 20, c);

		//分：秒の値を文字列化
		if (second < 10)
			swprintf_s(str, L"%d:0%d", minute, second);//秒の1桁目に0を用意
		else
			swprintf_s(str, L"%d:%d", minute, second);

		Font::StrDraw(str, 27, 85, 28, c);
	//}

	/*if (minute == 1 && second == 0 || minute == 0)
	{
		Font::StrDraw(str, 10, 85, 28, r);
	}*/
}