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
	m_Aitem_Font_x = 700.0f; //位置情報
	m_Aitem_Font_y = 500.0f;

	Aitem_Get_Font = 0; //アイテム把握変数
	
	//弾表示数変数
	m_Gun_num = 0; 

}

//アクション
void CObjAitemFont::Action()
{
	

}

//ドロー
void CObjAitemFont::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	wchar_t str[256];
	swprintf_s(str, L"ショットガンの弾%d発を獲得しました。", m_Gun_num);

	//1、ショット2、アサルト3、スナイパー4、レールガン弾5、レールガン弾6、グレネード7、体力8、アーマー

	Font::StrDraw(str, m_Aitem_Font_x, m_Aitem_Font_y, 20, c);

}