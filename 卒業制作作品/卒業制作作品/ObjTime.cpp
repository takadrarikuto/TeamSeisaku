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

//イニシャライズ
void CObjTime::Init()
{
	m_time = 10850;
	m_flag_time = true;
}

//アクション
void CObjTime::Action()
{
	if (Menu_flg == false)
	{
		if (m_time > 0)
		{
			m_time--;
		}
	}
	//m_time = 120;
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