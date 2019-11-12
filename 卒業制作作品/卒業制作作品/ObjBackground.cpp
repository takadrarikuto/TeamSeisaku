//使用すvxるヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameHead.h"
#include"GameL\WinInputs.h"

#include"ObjBackground.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void  C0bjBackground::Init()
{

}

//アクション
void  C0bjBackground::Action()
{

}

//ドロー
void C0bjBackground::Draw()
{
	//描写カラー情報　R=RED G=Green A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,5.0f };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;
	
	//描画
	dst.m_top = -100.0f;
	dst.m_left = -100.0f;
	dst.m_right = 900.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);
}