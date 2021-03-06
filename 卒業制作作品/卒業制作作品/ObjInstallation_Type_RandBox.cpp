//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include <time.h>

#include "GameHead.h"
#include "ObjInstallation_Type_RandBox.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjInstallation_Type_RandBox::CObjInstallation_Type_RandBox(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_IT_Rand_Box_x = x;
	m_IT_Rand_Box_y = y;

}

//イニシャライズ
void CObjInstallation_Type_RandBox::Init()
{
	//初期化
	m_IT_Rand_Box_vx = 0.0f; //位置更新
	m_IT_Rand_Box_vy = 0.0f;

	//HitBoxサイズ
	m_HitSize_x = 33;
	m_HitSize_y = 32;

	//フォント表示タイム
	m_Font_time = 0;

	//補充フラグ
	m_Replenishment_flg = false;
	//再補充タイム
	m_Replenishment_time = 0;
	//アイテムランダム選択変数 
	m_Rand_aitem_num = 0;

	//再補充完了フォント表示フラグ
	m_Replenishment_Font_flg = false;
	//再補充完了フォント表示タイム
	m_Replenishment_Font_time = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_IT_Rand_Box_x, m_IT_Rand_Box_y, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_RANDBOX, 6);

}

//アクション
void CObjInstallation_Type_RandBox::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBoxの内容を更新 
	CHitBox* hit_gen = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_gen->SetPos(m_IT_Rand_Box_x, m_IT_Rand_Box_y); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_Font_time = 90; //フォント表示タイム設定
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			m_Rand_aitem_num = rand() % 100;

			if (m_Rand_aitem_num >= 0 && m_Rand_aitem_num <= 30)
			{
				aitemfont->SetAGF(7);
				aitemfont->SetAitemNum(200);
				hero->SetHP(200); //体力
				Audio::Start(12); //効果音再生
			}
			else if (m_Rand_aitem_num > 30 && m_Rand_aitem_num <= 60)
			{
				aitemfont->SetAGF(8);
				aitemfont->SetAitemNum(150);
				hero->SetEN(150); //アーマー
				hero->SetHP_F(false);
				hero->SetEN_F(true); //アーマー回復確認
				Audio::Start(12); //効果音再生
			}
			else if (m_Rand_aitem_num > 60 && m_Rand_aitem_num <= 80)
			{
				aitemfont->SetAGF(4);
				aitemfont->SetAitemNum(2);
				hero->SetRL(2);
				((UserData*)Save::GetData())->RL_load += 2;//ロケットランチャー
				Audio::Start(12); //効果音再生
			}
			else if (m_Rand_aitem_num > 80 && m_Rand_aitem_num <= 85)
			{
				aitemfont->SetAGF(5);
				aitemfont->SetAitemNum(1);
				hero->SetRG(1);
				((UserData*)Save::GetData())->RG_load += 1;//レールガン弾数回復
				Audio::Start(12); //効果音再生
			}
			else if (m_Rand_aitem_num > 85 && m_Rand_aitem_num <= 99)
			{
				aitemfont->SetAGF(6);
				aitemfont->SetAitemNum(3);
				hero->SetGRE(3); //グレネード
				Audio::Start(12); //効果音再生
			}

			//補充フラグ
			m_Replenishment_flg = true;
			//再補充タイム
			m_Replenishment_time = 3600;
			//再補充完了フォント表示タイム
			m_Replenishment_Font_time = REPLENIShHMENT_FONT_TIME;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	//主人公の移動に合わせる
	m_IT_Rand_Box_x -= hvx;
	m_IT_Rand_Box_y -= hvy;

	//フォント表示タイム減少処理
	//0になるまで減少
	if (m_Font_time > 0)
	{
		m_Font_time--;
	}

	if (Menu_flg == false)
	{
		//再補充タイム
		if (m_Replenishment_time > 0)
		{
			m_Replenishment_time--;
		}
		else if (m_Replenishment_time == 0)
		{
			//再補充完了フォント表示タイム減少処理
			if (m_Replenishment_Font_time > 0)
			{
				//効果音再生
				if (m_Replenishment_Font_time == REPLENIShHMENT_FONT_TIME)
				{
					m_Replenishment_Font_flg = true; //再補充完了フォント表示
					Audio::Start(8);
				}

				m_Replenishment_Font_time--; //再補充完了フォント表示タイム減少									
			}
			else if (m_Replenishment_Font_time == 0)
			{
				//再補充完了フォント表示フラグ初期化
				m_Replenishment_Font_flg = false;
			}
		}
	}
	
}

//ドロー
void CObjInstallation_Type_RandBox::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };

	wchar_t str[256];
	wchar_t str_f[256];

	//フォント表示処理
	if (m_Replenishment_Font_time > 0 && m_Replenishment_Font_flg == true)
	{
		swprintf_s(str, L"ランダムで資材が再補充されました。"); //再補充フォント表示
		Font::StrDraw(str, 0, 570, 30, c);
	}
	if (m_Font_time > 0)
	{
		swprintf_s(str_f, L"エンターキーでアイテム補充"); //操作説明フォント表示
		Font::StrDraw(str_f, m_IT_Rand_Box_x - 80, m_IT_Rand_Box_y - 90, 15, blk);
	}

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 300.0f;
	src.m_left = 432.0f;
	src.m_right = 465.0f;
	src.m_bottom = 332.0f;

	//描画処理
	dst.m_top = 0.0f + m_IT_Rand_Box_y;
	dst.m_left = 0.0f + m_IT_Rand_Box_x;
	dst.m_right = 33.0f + m_IT_Rand_Box_x;
	dst.m_bottom = 32.0f + m_IT_Rand_Box_y;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}