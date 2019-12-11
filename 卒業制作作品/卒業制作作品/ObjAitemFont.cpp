//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjAitemFont.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjAitemFont::Init()
{
	//初期化
	m_Aitem_Font_x = 0.0f; //位置情報
	m_Aitem_Font_y = 570.0f;

	Aitem_Get_Font = 0; //アイテム把握変数
	
	//アイテム表示数変数
	m_Aitem_num = 0;

	//フォント表示タイム
	m_Font_time = 0;
	//フォント表示フラグ
	m_Font_flg = false; 

	//ツールボックス画像表示フラグ
	m_ToolBox_flg = false;

}

//アクション
void CObjAitemFont::Action()
{
	if (Aitem_Get_Font > 0)
	{
		m_Font_time++;
		if (m_Font_time > 120)
		{
			Aitem_Get_Font = 0;
			m_Font_time = 0;
		}		
	}
	
}

//ドロー
void CObjAitemFont::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒
	float fc[4] = { 0.0f ,0.0f, 0.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//1、ショット2、アサルト3、スナイパー4、レールガン弾5
	//レールガン弾6、グレネード7、体力8、アーマー、ツールボックス9
	//表示処理
	
	if (Aitem_Get_Font > 0)
	{
		if (Aitem_Get_Font == 1)
		{
			swprintf_s(str, L"ショットガンの弾%d発獲得しました。", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 2)
		{
			swprintf_s(str, L"アサルトライフルの弾%d発獲得しました。", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 3)
		{
			swprintf_s(str, L"スナイパーライフルの弾%d発獲得しました。", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 4)
		{
			swprintf_s(str, L"ロケットランチャーの弾%d発獲得しました。", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 5)
		{
			swprintf_s(str, L"レールガンの弾%d発獲得しました。", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 6)
		{
			swprintf_s(str, L"グレネード%d個獲得しました。", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 7)
		{
			swprintf_s(str, L"回復箱を獲得しました。");
		}
		else if (Aitem_Get_Font == 8)
		{
			swprintf_s(str, L"アーマーを獲得しました。");
		}
		else if (Aitem_Get_Font == 9)
		{
			swprintf_s(str, L"ツールボックスを獲得しました。");
		}		
		Font::StrDraw(str, m_Aitem_Font_x, m_Aitem_Font_y, 30, blk); //アイテム取得でフォント表示
	}	
	

	//切り取り処理
	src.m_top = 60.0f;
	src.m_left = 4.0f;
	src.m_right = 40.0f;
	src.m_bottom = 94.0f;

	//描画処理
	dst.m_top = 750.0f;
	dst.m_left = 550.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	if (m_ToolBox_flg == true)
	{
		Draw::Draw(7, &src, &dst, c, 0.0f);
	}
	

}